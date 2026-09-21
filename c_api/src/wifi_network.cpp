#include <wifi_pc_c_api/wifi_network.h>
#include <wifi_pc/wifi_network.hpp>
#include <stdint.h>
#include <string>

uint8_t wpc_wifi_network_is_secured(const WpcWifiNetwork* context) {
    auto wifi_network = (wpc::WifiNetwork*) context;
    return wifi_network->IsSecured() ? 1 : 0;
}

const char* wpc_wifi_network_name(const WpcWifiNetwork* context) {
    auto wifi_network = (wpc::WifiNetwork*) context;

    return wifi_network->name().data();
}

uint8_t wpc_wifi_network_signal_quality(const WpcWifiNetwork* context) {
    auto wifi_network = (wpc::WifiNetwork*) context;

    return (uint8_t) wifi_network->signal_quality();
}