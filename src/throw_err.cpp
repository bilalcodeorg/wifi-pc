#include <wifi_pc/throw_err.hpp>
#include <stdexcept>
#include <string>

void wifi_pc::ThrowError::General()
{
	General("something went wrong");
}

void wifi_pc::ThrowError::General(const std::string& msg)
{
	throw std::runtime_error("Error: " + msg);
}

void wifi_pc::ThrowError::WifiAdapterNotFound()
{
	std::string msg = "failed to initialize Wi-Fi adapter";
	WifiAdapterNotFound(msg);
}

void wifi_pc::ThrowError::WifiAdapterNotFound(const std::string& msg)
{
	throw std::runtime_error("WifiAdapterNotFound: " + msg);
}

void wifi_pc::ThrowError::UnsupportedPlatform()
{
	UnsupportedPlatform("current platform not supported");
}

void wifi_pc::ThrowError::UnsupportedPlatform(const std::string& msg)
{
	throw std::runtime_error("UnsupportedPlatform: " + msg);
}
