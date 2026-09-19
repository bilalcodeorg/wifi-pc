#include <wifi_pc/scan.hpp>
#include <wifi_pc/types.hpp>
#include <wifi_pc/wifi_network.hpp>
#include <wifi_pc/throw_err.hpp>
#include <windows/wifi_scan.hpp>

wpc::Scan::Scan() {
#ifdef _WIN32
	windows::Wifi::ScanNetworks(this->networks_);
#else
	wpc::ThrowError::UnsupportedPlatform();
#endif

	// Updating wifi name list
	for (const auto& network : this->networks()) {
		this->network_names_.push_back(network.name());
	}
}

const wpc::type::WifiNames& wpc::Scan::network_names() const
{
	return this->network_names_;
}

const wpc::type::WifiNetworks& wpc::Scan::networks() const
{
	return this->networks_;
}