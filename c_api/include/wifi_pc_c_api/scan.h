#pragma once

#include <wifi_pc_c_api/export.h>
#include <wifi_pc_c_api/list.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

WIFI_PC_API typedef struct WifiPcScan WifiPcScan;
WIFI_PC_API WifiPcScan* wifi_pc_scan_new();
WIFI_PC_API const WifiPcWifiNames* wifi_pc_scan_network_names(
    const WifiPcScan* context
);
WIFI_PC_API const WifiPcWifiNetworks* wifi_pc_scan_networks(
    const WifiPcScan* context
);
WIFI_PC_API void wifi_pc_scan_destroy(WifiPcScan* context);

#ifdef __cplusplus
}
#endif // __cplusplus