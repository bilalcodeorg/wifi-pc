#pragma once

#include <netlink/netlink.h>
#include <netlink/genl/genl.h>
#include <netlink/genl/ctrl.h>


namespace wpc { namespace linux_wifi_fn {

    typedef struct {
        char ssid[33];
        int  signal;          /* 0..100 */
        char security[32];
    } ap_t;

    typedef struct {
        int ifindex;
        int status;      /* 0 = waiting, 1 = done, 2 = aborted */
    } ev_state;

    ap_t ap_list[MAX_AP];
    int  ap_count = 0;
    int  max_age_ms = 0;   /* 0 = no age filter */
    
    
    long now_ms();

    int cmp_str(const void *a, const void *b);

    int find_adapters(char names[][IFNAMSIZ], int max);

    void parse_ies(
        const uint8_t *ie, int len, int privacy, ap_t *ap, int *hidden
    );

    int scan_dump_cb(struct nl_msg *msg, void *arg);

    int ev_cb(struct nl_msg *msg, void *arg);

    int cmp_signal_desc(const void *a, const void *b);

    void print_results(const char *iface);
    

    void clear_memory(struct nl_sock* cmd, struct nl_sock* ev);
    
}}