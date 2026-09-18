#pragma once

#include <wifi_pc_c_api/export.h>
#include <wifi_pc_c_api/wifi_network.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

WIFI_PC_API typedef struct WifiPcWifiNames WifiPcWifiNames;
WIFI_PC_API const char* wifi_pc_wifi_names_at(
    const WifiPcWifiNames* context, int index
);
WIFI_PC_API int wifi_pc_wifi_names_size(const WifiPcWifiNames* context);

WIFI_PC_API typedef struct WifiPcWifiNetworks WifiPcWifiNetworks;
WIFI_PC_API const WifiPcWifiNetwork* wifi_pc_wifi_networks_at(
    const WifiPcWifiNetworks* context, int index
);
WIFI_PC_API int wifi_pc_wifi_networks_size(const WifiPcWifiNetworks* context);

#ifdef __cplusplus
}
#endif // __cplusplus