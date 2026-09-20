#include <wifi_pc_c_api/scan.h>
#include <wifi_pc_c_api/enum.h>
#include <wifi_pc/scan.hpp>
#include <wifi_pc/error.hpp>

extern "C" {

WPC_API WpcCode wpc_scan_new(WpcScan* context) {
    try {
        context = (WpcScan*) new wpc::Scan();
    }
    catch (const wpc::Error& e) {
        switch (e.code()) {
            case wpc::err_code::kOsError:
                return kWpcOsError;

            case wpc::err_code::kNoAdapter:
                return kWpcNoAdapterError;

            default:
                return kWpcError;
        }
    }
    return kWpcSuccess;
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