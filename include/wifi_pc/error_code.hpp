#pragma once
#include <string>

namespace wpc::err_code {

typedef enum {
    kNoError,
    kGeneral,
    kOsError,
    kNoAdapter,
    kUnsupportedPlatform,
    kWifiOff
} ErrorCode;

};
namespace wpc::err_text {

const std::string kUnsupportedPlatform = 
    "UnsupportedPlatform: This platform or operating system is not supported to scan wifi on it.";

const std::string kWifiOff = 
    "WifiOff: Your system wifi might be turned off";

};