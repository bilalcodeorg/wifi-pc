#include <wifi_scan.hpp>
#include <wifi_scan_helper.hpp>
#include <net/if.h>
#include <errno.h>
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

using namespace wpc::linux_wifi_fn;

#define SCAN_TIMEOUT_MS 3000
#define MAX_AP          256
#define MAX_IFACES      16

void wpc::linux::run() {

    ap_t ap_list[MAX_AP];
    int  ap_count = 0;
    int  max_age_ms = 0;   /* 0 = no age filter */

    // For command line arguments
    size_t argc = 0;
    char **argv = nullptr;

    long start = now_ms();
    char adapters[MAX_IFACES][IFNAMSIZ];
    char iface[IFNAMSIZ];
    struct nl_sock *cmd = NULL, *ev = NULL;
    int ifindex;
    int family = -1;
    ev_state st = {0, 0};
    int have_events = 0;
    int grp;
    int triggered = 0;
    long scan_start;

    int n = find_adapters(adapters, MAX_IFACES);
    if (n == 0 && argc < 2) {
        fprintf(stderr, "No wireless adapter found.\n");
        // return 1;-----------------------------------------------------------------------------------
    }

    if (n > 0) {
        fprintf(stderr, "Detected wireless adapter(s):");
        for (int i = 0; i < n; i++)
            fprintf(stderr, " %s%s", adapters[i], (i == 0 && argc < 2) ? "(default)" : "");
        fprintf(stderr, "\n");
    }

    if (argc > 1) {
        strncpy(iface, argv[1], IFNAMSIZ - 1);
        iface[IFNAMSIZ - 1] = '\0';
    } else {
        memcpy(iface, adapters[0], IFNAMSIZ);
    }

    ifindex = if_nametoindex(iface);
    if (!ifindex) {
        fprintf(stderr, "Interface '%s' not found.\n", iface);
        // return 1;-----------------------------------------------------------------------------------
    }

    cmd = nl_socket_alloc();
    ev  = nl_socket_alloc();
    if (!cmd || !ev) {
        fprintf(stderr, "Failed to allocate netlink sockets.\n");
        // return 1;-----------------------------------------------------------------------------------
        clear_memory(cmd, ev);
    }
    if (genl_connect(cmd) || genl_connect(ev)) {
        fprintf(stderr, "Failed to connect to generic netlink.\n");
        clear_memory(cmd, ev);
    }

    family = genl_ctrl_resolve(cmd, "nl80211");
    if (family < 0) {
        fprintf(stderr, "nl80211 not available (is cfg80211 loaded?).\n");
        // goto out;
        clear_memory(cmd, ev);
    }

    st.ifindex = ifindex;

    grp = genl_ctrl_resolve_grp(ev, "nl80211", "scan");
    if (grp >= 0 && nl_socket_add_membership(ev, grp) == 0) {
        nl_socket_disable_seq_check(ev);
        nl_socket_modify_cb(ev, NL_CB_VALID, NL_CB_CUSTOM, ev_cb, &st);
        have_events = 1;
    }

    scan_start = now_ms();
    {
        struct nl_msg *msg = nlmsg_alloc();
        struct nl_msg *ssids = nlmsg_alloc();
        if (!msg || !ssids) {
            fprintf(stderr, "Out of memory.\n");
            if (msg) nlmsg_free(msg);
            if (ssids) nlmsg_free(ssids);
            // goto out;
            clear_memory(cmd, ev);
        }
        genlmsg_put(msg, 0, 0, family, 0, 0, NL80211_CMD_TRIGGER_SCAN, 0);
        nla_put_u32(msg, NL80211_ATTR_IFINDEX, ifindex);
        nla_put(ssids, 1, 0, "");                         /* wildcard SSID */
        nla_put_nested(msg, NL80211_ATTR_SCAN_SSIDS, ssids);
        nlmsg_free(ssids);

        int err = nl_send_sync(cmd, msg);                 /* frees msg */
        if (err >= 0 || err == -NLE_BUSY) {
            triggered = 1;                                /* BUSY = scan already running */
        } else {
            fprintf(stderr,
                    "Note: could not trigger new scan (%s). "
                    "Run as root for a fresh scan; showing cached results.\n",
                    nl_geterror(err));
        }
    }

    if (triggered && have_events) {
        struct pollfd pfd = { nl_socket_get_fd(ev), POLLIN, 0 };
        while (st.status == 0) {
            long remaining = SCAN_TIMEOUT_MS - (now_ms() - scan_start);
            if (remaining <= 0)
                break;
            int r = poll(&pfd, 1, (int)remaining);
            if (r > 0)
                nl_recvmsgs_default(ev);
            else if (r == 0)
                break;
            else if (errno != EINTR)
                break;
        }
        if (st.status == 0)
            fprintf(stderr, "Note: 3s scan limit reached; showing results gathered so far.\n");
    }

    /* only drop stale entries when we know a fresh scan really completed */
    max_age_ms = (triggered && have_events && st.status == 1) ? 15000 : 0;
    nl_socket_modify_cb(cmd, NL_CB_VALID, NL_CB_CUSTOM, scan_dump_cb, NULL);
    {
        struct nl_msg *msg = nlmsg_alloc();
        if (!msg) {
            fprintf(stderr, "Out of memory.\n");
            // goto out;
            clear_memory(cmd, ev);
        }
        genlmsg_put(msg, 0, 0, family, 0, NLM_F_DUMP, NL80211_CMD_GET_SCAN, 0);
        nla_put_u32(msg, NL80211_ATTR_IFINDEX, ifindex);
        int err = nl_send_auto(cmd, msg);
        nlmsg_free(msg);                                  /* nl_send_auto does not free */
        if (err >= 0)
            err = nl_recvmsgs_default(cmd);               /* reads multipart dump until DONE */
        if (err < 0) {
            fprintf(stderr, "Failed to read scan results: %s\n", nl_geterror(err));
            // goto out;
            clear_memory(cmd, ev);
        }
    }

    print_results(iface);
    fprintf(stderr, "Scan time: %ld ms\n", now_ms() - start);

// out:
}