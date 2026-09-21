#include <wifi_pc/scan.hpp>
#include <wifi_pc/types.hpp>
#include <wifi_pc/wifi_network.hpp>
#include <wifi_pc/error.hpp>
#include <windows/wifi_scan.hpp>

wpc::Scan::Scan() {
#ifdef _WIN32
	windows::Wifi::ScanNetworks(this->networks_);
#else
	throw wpc::error::UnsupportedPlatform();
#endif

	// Updating wifi name list
	for (const auto& network : this->networks()) {
		this->network_names_.push_back(network.name());
	}
}

const wpc::WifiNameList& wpc::Scan::network_names() const
{
	return this->network_names_;
}

const wpc::WifiNetworkList& wpc::Scan::networks() const
{
	return this->networks_;
}