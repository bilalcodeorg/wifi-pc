#include <wifi_pc_c_api/scan.h>
#include <wifi_pc_c_api/error.h>
#include <wifi_pc_c_api/error_enum.h>
#include <wifi_pc/scan.hpp>
#include <wifi_pc/error.hpp>

extern "C" {

WpcScan* wpc_scan_new() {
    WpcScan* scan = nullptr;
    try {
        scan = (WpcScan*) new wpc::Scan();
    }
    catch (const wpc::Error& e) {
        scan = nullptr;

        switch (e.code()) {
            case wpc::err_code::kOsError:
                wpc_set_last_error(kWpcErrorOs, e.what());
                break;
            case wpc::err_code::kNoAdapter:
                wpc_set_last_error(kWpcErrorNoAdapter, e.what());
                break;
            default:
                wpc_set_last_error(kWpcErrorGeneral, e.what());
        }
    }
    return scan;
}

const WpcWifiNameList* wpc_scan_network_names(const WpcScan* context) {
    auto scan = (wpc::Scan*) context;
    return (WpcWifiNameList*) &scan->network_names();
}

const WpcWifiNetworkList* wpc_scan_networks(const WpcScan* context) {
    auto scan = (wpc::Scan*) context;
    return (WpcWifiNetworkList*) &scan->networks();
}

void wpc_scan_destroy(WpcScan* context) {
    auto scan = (wpc::Scan*)context;
    delete scan;
}

} // extern "C"