#pragma once

#include <wifi_pc_c_api/export.h>
#include <wifi_pc_c_api/list.h>
#include <wifi_pc_c_api/enum.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct WpcScan WpcScan;
WPC_API WpcCode wpc_scan_new(WpcScan* context);
WPC_API const WpcWifiNameList* wpc_scan_network_names(const WpcScan* context);
WPC_API const WpcWifiNetworkList* wpc_scan_networks(const WpcScan* context);
WPC_API void wpc_scan_destroy(WpcScan* context);

#ifdef __cplusplus
}
#endif // __cplusplus