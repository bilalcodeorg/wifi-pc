#include <wifi_pc/scan.hpp>
#include <wifi_pc/types.hpp>
#include <wifi_pc/wifi_network.hpp>
#include <wifi_pc/throw_err.hpp>
#include <windows_wifi_scan.hpp>

wifi_pc::Scan::Scan()
{
#ifdef _WIN32
	this->networks_ = windows::Wifi::ScanNetworks();
#else
	wifi_pc::ThrowError::UnsupportedPlatform();
#endif

}

const wifi_pc::type::StringList wifi_pc::Scan::network_names() const
{
	auto network_names = std::make_unique<std::vector<std::string>>();

	for (const auto& network : *this->networks()) {
		network_names->push_back(network->name());
	}

	return network_names;
}

const std::unique_ptr<wifi_pc::type::WifiNetList>& wifi_pc::Scan::networks() const
{
	return this->networks_;
}