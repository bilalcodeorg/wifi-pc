#include <wifi_pc/throw_err.hpp>
#include <stdexcept>
#include <string>

void ThrowError::WifiAdapterNotFound()
{
	std::string msg = "failed to initialize Wi-Fi adapter";
	ThrowError::WifiAdapterNotFound(msg);
}

void ThrowError::WifiAdapterNotFound(std::string& msg)
{
	throw std::runtime_error("WifiAdapterNotFound: " + current_msg);
}
