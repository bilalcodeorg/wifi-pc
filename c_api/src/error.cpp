#include <wifi_pc_c_api/error.h>
#include <wifi_pc_c_api/error_enum.h>
#include <string>

thread_local WpcErrorCode kWpcLastErrorCode = kWpcErrorNotPresent;
thread_local std::string kWpcLastErrorReason = "";

WpcErrorCode wpc_last_error_code() {
    return kWpcLastErrorCode;
}

const char* wpc_last_error_reason() {
    return kWpcLastErrorReason.data();
}

void wpc_set_last_error(WpcErrorCode error_code, const char* reason) {
    wpc_set_last_error_code(error_code);
    wpc_set_last_error_reaon(reason);
}


void wpc_set_last_error_code(WpcErrorCode error_code) {
    kWpcLastErrorCode = error_code;
}

void wpc_set_last_error_reaon(const char* reason) {
    kWpcLastErrorReason = std::string(reason);
}