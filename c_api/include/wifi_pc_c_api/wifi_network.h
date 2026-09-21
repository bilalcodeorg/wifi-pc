#pragma once

#include <wifi_pc_c_api/export.h>
#include <stdint.h>

typedef struct WpcWifiNetwork WpcWifiNetwork;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

WPC_API uint8_t wpc_wifi_network_is_secured(const WpcWifiNetwork* context);
WPC_API const char* wpc_wifi_network_name(const WpcWifiNetwork* context);
WPC_API uint8_t wpc_wifi_network_signal_quality(const WpcWifiNetwork* context);

#ifdef __cplusplus
}
#endif // __cplusplus