#pragma once

namespace wpc::err_code {

typedef enum {
    kGeneral,
    kOsError,
    kNoAdapter,
    kUnsupportedPlatform
} ErrorCode;

};