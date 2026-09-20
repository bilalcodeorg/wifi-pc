#include <wifi_pc/error.hpp>
#include <stdexcept>

wpc::Error::Error(err_code::ErrorCode error_code, const std::string& reason)
    : Error::runtime_error{reason}, error_code_{error_code} {}

const wpc::err_code::ErrorCode& wpc::Error::code() const {
    return this->error_code_;
}