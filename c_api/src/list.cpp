#include <wifi_pc_c_api/list.h>
#include <wifi_pc/types.hpp>
#include <stdint.h>

const char* wpc_wifi_name_list_at(
    const WpcWifiNameList* context, uint64_t index
) {
    auto names = (wpc::WifiNameList*) context;
    return (*names)[index].data();
}

const WpcWifiNetwork* wpc_wifi_network_list_at(
    const WpcWifiNetworkList* context, uint64_t index
) {
    auto names = (wpc::WifiNetworkList*) context;

    return (WpcWifiNetwork*) &(*names)[index];
}

uint64_t wpc_wifi_name_list_size(const WpcWifiNameList* context) {
    auto names = (wpc::WifiNameList*) context;
    return (uint64_t) names->size();
}

uint64_t wpc_wifi_network_list_size(const WpcWifiNetworkList* context) {
    auto names = (wpc::WifiNetworkList*) context;
    return (uint64_t) names->size();
}