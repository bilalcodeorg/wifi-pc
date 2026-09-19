#include <wifi_pc_c_api/scan.h>
#include <wifi_pc/scan.hpp>

extern "C" {

WifiPcScan* wifi_pc_scan_new() {
    auto scan = new wpc::Scan();
    return (WifiPcScan*) scan;
}

const WifiPcWifiNames* wifi_pc_scan_network_names(const WifiPcScan* context) {
    auto scan = (wpc::Scan*) context;
    return (WifiPcWifiNames*) &scan->network_names();
}

const WifiPcWifiNetworks* wifi_pc_scan_networks(const WifiPcScan* context) {
    auto scan = (wpc::Scan*) context;
    return (WifiPcWifiNetworks*) &scan->networks();
}

void wifi_pc_scan_destroy(WifiPcScan* context) {
    auto scan = (wpc::Scan*)context;
    delete scan;
}

} // extern "C"