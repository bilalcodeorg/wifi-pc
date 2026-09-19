#pragma once

#include <vector>
#include <string>
#include <memory>
#include <wifi_pc/types.hpp>
#include <wifi_pc/wifi_network.hpp>

namespace wpc {
	class Scan {
	private:
		type::WifiNetworks networks_;
		type::WifiNames network_names_;
	public:
		Scan();
		const type::WifiNames& network_names() const;
		const type::WifiNetworks& networks() const;
	};
};