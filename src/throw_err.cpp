#include <wifi_pc/throw_err.hpp>
#include <stdexcept>
#include <string>

void wpc::ThrowError::General()
{
	General("something went wrong");
}

void wpc::ThrowError::General(const std::string& msg)
{
	throw std::runtime_error("Error: " + msg);
}

void wpc::ThrowError::WifiAdapterNotFound()
{
	std::string msg = "failed to initialize Wi-Fi adapter";
	WifiAdapterNotFound(msg);
}

void wpc::ThrowError::WifiAdapterNotFound(const std::string& msg)
{
	throw std::runtime_error("WifiAdapterNotFound: " + msg);
}

void wpc::ThrowError::UnsupportedPlatform()
{
	UnsupportedPlatform("current platform not supported");
}

void wpc::ThrowError::UnsupportedPlatform(const std::string& msg)
{
	throw std::runtime_error("UnsupportedPlatform: " + msg);
}
