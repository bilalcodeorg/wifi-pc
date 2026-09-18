#include <wifi_pc_c_api/wifi_network.h>
#include <wifi_pc/wifi_network.hpp>
#include <string>

extern "C" {

uint8_t wifi_pc_wifi_network_is_secured(const WifiPcWifiNetwork* context) {
    auto wifi_network = (wifi_pc::WifiNetwork*) context;
    return wifi_network->IsSecured() ? 1 : 0;
}

const char* wifi_pc_wifi_network_name(const WifiPcWifiNetwork* context) {
    auto wifi_network = (wifi_pc::WifiNetwork*) context;

    return wifi_network->name().data();
}

int wifi_pc_wifi_network_signal_quality(const WifiPcWifiNetwork* context) {
    auto wifi_network = (wifi_pc::WifiNetwork*) context;

    return wifi_network->signal_quality();
}

} // extern "C"