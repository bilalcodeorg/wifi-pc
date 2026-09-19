#include <wifi_pc_c_api/list.h>
#include <wifi_pc/types.hpp>

const char* wpc_wifi_names_at(const WpcWifiNames* context, int index) {
    auto names = (wpc::type::WifiNames*) context;
    return (*names)[index].data();
}

int wpc_wifi_names_size(const WpcWifiNames* context) {
    auto names = (wpc::type::WifiNames*) context;
    return names->size();
}

const WpcWifiNetwork* wpc_wifi_networks_at(
    const WpcWifiNetworks* context, int index
) {
    auto names = (wpc::type::WifiNetworks*) context;

    return (WpcWifiNetwork*) &(*names)[index];
}

int wpc_wifi_networks_size(const WpcWifiNetworks* context) {
    auto names = (wpc::type::WifiNetworks*) context;
    return names->size();
}