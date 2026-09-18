#pragma once

#include <wifi_pc_c_api/export.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct WifiPcWifiNetwork WifiPcWifiNetwork;

WIFI_PC_API uint8_t wifi_pc_wifi_network_is_secured(
    const WifiPcWifiNetwork* context
);
WIFI_PC_API const char* wifi_pc_wifi_network_name(
    const WifiPcWifiNetwork* context
);
WIFI_PC_API int wifi_pc_wifi_network_signal_quality(
    const WifiPcWifiNetwork* context
);

#ifdef __cplusplus
}
#endif // __cplusplus