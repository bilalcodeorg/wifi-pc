#include <wifi_scan_helper.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>
#include <poll.h>
#include <time.h>
#include <ctype.h>
#include <net/if.h>
#include <linux/nl80211.h>

long wpc::linux_wifi_fn::now_ms() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000L + ts.tv_nsec / 1000000L;
}

int wpc::linux_wifi_fn::cmp_str(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

int wpc::linux_wifi_fn::find_adapters(char names[][IFNAMSIZ], int max) {
    DIR *d = opendir("/sys/class/net");
    if (!d)
        return 0;

    int n = 0;
    struct dirent *e;
    while ((e = readdir(d)) != NULL && n < max) {
        if (e->d_name[0] == '.')
            continue;
        if (strlen(e->d_name) >= IFNAMSIZ)
            continue;
        char path[512];
        snprintf(path, sizeof(path), "/sys/class/net/%s/wireless", e->d_name);
        int is_wifi = (access(path, F_OK) == 0);
        if (!is_wifi) {
            snprintf(path, sizeof(path), "/sys/class/net/%s/phy80211", e->d_name);
            is_wifi = (access(path, F_OK) == 0);
        }
        if (is_wifi) {
            memset(names[n], 0, IFNAMSIZ);
            memcpy(names[n], e->d_name, strlen(e->d_name));
            n++;
        }
    }
    closedir(d);

    qsort(names, n, IFNAMSIZ, cmp_str);
    return n;
}

void wpc::linux_wifi_fn::parse_ies(
    const uint8_t *ie, int len, int privacy, ap_t *ap, int *hidden
) {
    int has_rsn = 0, has_wpa = 0;
    int sae = 0, psk = 0, eap = 0, owe = 0;

    ap->ssid[0] = '\0';
    *hidden = 1;

    while (len >= 2) {
        int id = ie[0], l = ie[1];
        if (l + 2 > len)
            break;
        const uint8_t *d = ie + 2;

        if (id == 0) {                                   /* SSID */
            int n = l > 32 ? 32 : l;
            int nonzero = 0;
            for (int i = 0; i < n; i++)
                if (d[i]) nonzero = 1;
            if (n > 0 && nonzero) {
                memcpy(ap->ssid, d, n);
                ap->ssid[n] = '\0';
                for (int i = 0; i < n; i++)              /* sanitize control chars */
                    if (!isprint((unsigned char)ap->ssid[i]) && (unsigned char)ap->ssid[i] < 0x80)
                        ap->ssid[i] = '?';
                *hidden = 0;
            }
        } else if (id == 48 && l >= 2) {                 /* RSN (WPA2/WPA3) */
            has_rsn = 1;
            int off = 2 + 4;                             /* version + group cipher */
            if (off + 2 <= l) {
                int pc = d[off] | (d[off + 1] << 8);
                off += 2 + pc * 4;
                if (off + 2 <= l) {
                    int ac = d[off] | (d[off + 1] << 8);
                    off += 2;
                    for (int i = 0; i < ac && off + 4 <= l; i++, off += 4) {
                        if (d[off] == 0x00 && d[off + 1] == 0x0f && d[off + 2] == 0xac) {
                            switch (d[off + 3]) {
                            case 1: case 3: case 5: case 11: case 12: case 13:
                                eap = 1; break;
                            case 2: case 4: case 6:
                                psk = 1; break;
                            case 8: case 9: case 24: case 25:
                                sae = 1; break;
                            case 18:
                                owe = 1; break;
                            }
                        }
                    }
                }
            }
        } else if (id == 221 && l >= 8 &&                /* Vendor WPA (WPA1) */
                   d[0] == 0x00 && d[1] == 0x50 && d[2] == 0xf2 && d[3] == 0x01) {
            has_wpa = 1;
        }

        ie += 2 + l;
        len -= 2 + l;
    }

    const char *s;
    if (has_rsn) {
        if (sae && psk)       s = "WPA2/WPA3-Personal";
        else if (sae)         s = "WPA3-Personal";
        else if (eap)         s = "WPA2-Enterprise";
        else if (owe)         s = "OWE (Enhanced Open)";
        else if (has_wpa)     s = "WPA/WPA2-Personal";
        else                  s = "WPA2-Personal";
    } else if (has_wpa) {
        s = "WPA-Personal";
    } else if (privacy) {
        s = "WEP";
    } else {
        s = "Open";
    }
    snprintf(ap->security, sizeof(ap->security), "%s", s);
}

int wpc::linux_wifi_fn::scan_dump_cb(struct nl_msg *msg, void *arg) {
    (void)arg;
    struct nlattr *tb[NL80211_ATTR_MAX + 1];
    struct nlattr *bss[NL80211_BSS_MAX + 1];
    struct genlmsghdr *gnlh =
        static_cast<struct genlmsghdr *>(nlmsg_data(nlmsg_hdr(msg)));

    nla_parse(tb, NL80211_ATTR_MAX, genlmsg_attrdata(gnlh, 0),
              genlmsg_attrlen(gnlh, 0), NULL);

    if (!tb[NL80211_ATTR_BSS])
        return NL_SKIP;
    if (nla_parse_nested(bss, NL80211_BSS_MAX, tb[NL80211_ATTR_BSS], NULL))
        return NL_SKIP;
    if (!bss[NL80211_BSS_INFORMATION_ELEMENTS])
        return NL_SKIP;

    if (max_age_ms && bss[NL80211_BSS_SEEN_MS_AGO] &&
        (int)nla_get_u32(bss[NL80211_BSS_SEEN_MS_AGO]) > max_age_ms)
        return NL_SKIP;

    int privacy = 0;
    if (bss[NL80211_BSS_CAPABILITY])
        privacy = (nla_get_u16(bss[NL80211_BSS_CAPABILITY]) & 0x0010) != 0;

    ap_t ap;
    memset(&ap, 0, sizeof(ap));
    int hidden;
    parse_ies(static_cast<const uint8_t *>(
                  nla_data(bss[NL80211_BSS_INFORMATION_ELEMENTS])),
              nla_len(bss[NL80211_BSS_INFORMATION_ELEMENTS]),
              privacy, &ap, &hidden);
    if (hidden)
        return NL_SKIP;

    int q = 0;
    if (bss[NL80211_BSS_SIGNAL_MBM]) {
        int dbm = (int32_t)nla_get_u32(bss[NL80211_BSS_SIGNAL_MBM]) / 100;
        q = 2 * (dbm + 100);                 /* -100 dBm => 0, -50 dBm => 100 */
    } else if (bss[NL80211_BSS_SIGNAL_UNSPEC]) {
        q = nla_get_u8(bss[NL80211_BSS_SIGNAL_UNSPEC]);
    }
    if (q < 0)   q = 0;
    if (q > 100) q = 100;
    ap.signal = q;

    for (int i = 0; i < ap_count; i++) {
        if (strcmp(ap_list[i].ssid, ap.ssid) == 0) {
            if (ap.signal > ap_list[i].signal)
                ap_list[i] = ap;
            return NL_SKIP;
        }
    }
    if (ap_count < MAX_AP)
        ap_list[ap_count++] = ap;

    return NL_SKIP;
}

int wpc::linux_wifi_fn::ev_cb(struct nl_msg *msg, void *arg) {
    wpc::linux_wifi_fn::ev_state *st = 
        static_cast<wpc::linux_wifi_fn::ev_state *>(arg);

    struct nlattr *tb[NL80211_ATTR_MAX + 1];
    struct genlmsghdr *gnlh =
        static_cast<struct genlmsghdr *>(nlmsg_data(nlmsg_hdr(msg)));

    nla_parse(tb, NL80211_ATTR_MAX, genlmsg_attrdata(gnlh, 0),
              genlmsg_attrlen(gnlh, 0), NULL);

    if (tb[NL80211_ATTR_IFINDEX] &&
        (int)nla_get_u32(tb[NL80211_ATTR_IFINDEX]) != st->ifindex)
        return NL_SKIP;

    if (gnlh->cmd == NL80211_CMD_NEW_SCAN_RESULTS)
        st->status = 1;
    else if (gnlh->cmd == NL80211_CMD_SCAN_ABORTED)
        st->status = 2;
    return NL_SKIP;
}

int wpc::linux_wifi_fn::cmp_signal_desc(const void *a, const void *b) {
    return ((const ap_t *)b)->signal - ((const ap_t *)a)->signal;
}

void wpc::linux_wifi_fn::print_results(const char *iface) {
    qsort(ap_list, ap_count, sizeof(ap_t), cmp_signal_desc);

    printf("Adapter: %s\n", iface);
    printf("%-32s  %-6s  %s\n", "SSID", "SIGNAL", "SECURITY");
    printf("%-32s  %-6s  %s\n", "--------------------------------", "------", "------------------");
    for (int i = 0; i < ap_count; i++)
        printf("%-32s  %-6d  %s\n", ap_list[i].ssid, ap_list[i].signal, ap_list[i].security);
    printf("\n%d network(s) found.\n", ap_count);
}

void wpc::linux_wifi_fn::clear_memory(struct nl_sock* cmd, struct nl_sock* ev) {
    if (cmd) nl_socket_free(cmd);
    if (ev)  nl_socket_free(ev);
}

