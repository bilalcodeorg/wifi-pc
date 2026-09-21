#pragma once

#include <wifi_pc_c_api/export.h>
#include <wifi_pc_c_api/wifi_network.h>
#include <stdint.h>

typedef struct WpcWifiNameList WpcWifiNameList;
typedef struct WpcWifiNetworkList WpcWifiNetworkList;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

WPC_API const char* wpc_wifi_name_list_at(
    const WpcWifiNameList* context, uint64_t index
);
WPC_API const WpcWifiNetwork* wpc_wifi_network_list_at(
    const WpcWifiNetworkList* context, uint64_t index
);

WPC_API uint64_t wpc_wifi_name_list_size(const WpcWifiNameList* context);
WPC_API uint64_t wpc_wifi_network_list_size(const WpcWifiNetworkList* context);

#ifdef __cplusplus
}
#endif // __cplusplus