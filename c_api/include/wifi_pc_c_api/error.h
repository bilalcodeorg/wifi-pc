#pragma once
#include <wifi_pc_c_api/export.h>
#include <wifi_pc_c_api/error_enum.h>

WPC_API void wpc_set_last_error(WpcErrorCode error_code, const char* reason);
WPC_API WpcErrorCode wpc_last_error_code();
WPC_API void wpc_set_last_error_code(WpcErrorCode error_code);
WPC_API const char* wpc_last_error_reason();
WPC_API void wpc_set_last_error_reaon(const char* reason);