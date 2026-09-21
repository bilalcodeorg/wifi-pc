#pragma once
#include <stdexcept>
#include <string>
#include <wifi_pc/error_code.hpp>

namespace wpc {

class Error : public std::runtime_error {
private:
    err_code::ErrorCode error_code_;
public:
    Error(err_code::ErrorCode error_code, const std::string& reason);
    const err_code::ErrorCode& code() const;
};

}; // namespace wpc

namespace wpc::error {

class GeneralError : public Error {
public:
    GeneralError(const std::string& reason);
};

class OsError : public Error {
public:
    OsError(const std::string& reason);
};

class NoAdapter : public Error {
public:
    NoAdapter(const std::string& reason);
};

class UnsupportedPlatform : public Error {
public:
    UnsupportedPlatform();
    UnsupportedPlatform(const std::string& reason);
};

class WifiOff : public Error {
public:
    WifiOff();
    WifiOff(const std::string& reason);
};

} // namespace wpc::error