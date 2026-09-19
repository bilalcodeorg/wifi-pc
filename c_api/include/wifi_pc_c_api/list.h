#pragma once

#include <wifi_pc_c_api/export.h>
#include <wifi_pc_c_api/wifi_network.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

WPC_API typedef struct WpcWifiNames WpcWifiNames;
WPC_API const char* wpc_wifi_names_at(
    const WpcWifiNames* context, int index
);
WPC_API int wpc_wifi_names_size(const WpcWifiNames* context);

WPC_API typedef struct WpcWifiNetworks WpcWifiNetworks;
WPC_API const WpcWifiNetwork* wpc_wifi_networks_at(
    const WpcWifiNetworks* context, int index
);
WPC_API int wpc_wifi_networks_size(const WpcWifiNetworks* context);

#ifdef __cplusplus
}
#endif // __cplusplus