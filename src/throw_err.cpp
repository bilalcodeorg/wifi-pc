#include <wifi_pc/throw_err.hpp>
#include <stdexcept>
#include <string>

void wifi_pc::ThrowError::WifiAdapterNotFound()
{
	std::string msg = "failed to initialize Wi-Fi adapter";
	ThrowError::WifiAdapterNotFound(msg);
}

void wifi_pc::ThrowError::WifiAdapterNotFound(std::string& msg)
{
	throw std::runtime_error("WifiAdapterNotFound: " + msg);
}