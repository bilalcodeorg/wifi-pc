#include <wifi_pc_c_api/list.h>
#include <wifi_pc/types.hpp>

const char* wifi_pc_wifi_names_at(const WifiPcWifiNames* context, int index) {
    auto names = (wpc::type::WifiNames*) context;
    return (*names)[index].data();
}

int wifi_pc_wifi_names_size(const WifiPcWifiNames* context) {
    auto names = (wpc::type::WifiNames*) context;
    return names->size();
}

const WifiPcWifiNetwork* wifi_pc_wifi_networks_at(
    const WifiPcWifiNetworks* context, int index
) {
    auto names = (wpc::type::WifiNetworks*) context;

    return (WifiPcWifiNetwork*) &(*names)[index];
}

int wifi_pc_wifi_networks_size(const WifiPcWifiNetworks* context) {
    auto names = (wpc::type::WifiNetworks*) context;
    return names->size();
}