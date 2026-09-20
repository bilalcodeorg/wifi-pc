#pragma once
#include <stdexcept>
#include <wifi_pc/error_code.hpp>

namespace wpc {

class Error : public std::runtime_error {
private:
    err_code::ErrorCode error_code_;
public:
    Error(err_code::ErrorCode error_code, const std::string& reason);
    const err_code::ErrorCode& code() const;
};

};