#include <wifi_pc_c_api/scan.h>
#include <wifi_pc/scan.hpp>

extern "C" {

WpcScan* wpc_scan_new() {
    auto scan = new wpc::Scan();
    return (WpcScan*) scan;
}

const WpcWifiNames* wpc_scan_network_names(const WpcScan* context) {
    auto scan = (wpc::Scan*) context;
    return (WpcWifiNames*) &scan->network_names();
}

const WpcWifiNetworks* wpc_scan_networks(const WpcScan* context) {
    auto scan = (wpc::Scan*) context;
    return (WpcWifiNetworks*) &scan->networks();
}

void wpc_scan_destroy(WpcScan* context) {
    auto scan = (wpc::Scan*)context;
    delete scan;
}

} // extern "C"