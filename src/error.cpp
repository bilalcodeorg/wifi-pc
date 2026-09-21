#include <wifi_pc/error.hpp>
#include <wifi_pc/error_code.hpp>
#include <stdexcept>

wpc::Error::Error(err_code::ErrorCode error_code, const std::string& reason)
    : Error::runtime_error{reason}, error_code_{error_code} {}

const wpc::err_code::ErrorCode& wpc::Error::code() const {
    return this->error_code_;
}

wpc::error::GeneralError::GeneralError(const std::string& reason)
    : Error{err_code::kGeneral, reason} {}

wpc::error::OsError::OsError(const std::string& reason)
    : Error{err_code::kOsError, reason} {}

wpc::error::NoAdapter::NoAdapter(const std::string& reason)
    : Error{err_code::kNoAdapter, reason} {}

wpc::error::UnsupportedPlatform::UnsupportedPlatform()
    : Error{err_code::kUnsupportedPlatform, err_text::kUnsupportedPlatform} {}

wpc::error::UnsupportedPlatform::UnsupportedPlatform(const std::string& reason)
    : Error{err_code::kUnsupportedPlatform, reason} {}

wpc::error::WifiOff::WifiOff()
    : Error{err_code::kWifiOff, err_text::kWifiOff} {}

wpc::error::WifiOff::WifiOff(const std::string& reason)
    : Error{err_code::kWifiOff, reason} {}