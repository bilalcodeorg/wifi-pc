#pragma once

#include <vector>
#include <string>
#include <memory>
#include <wifi_pc/types.hpp>
#include <wifi_pc/wifi_network.hpp>

namespace wpc {
	class Scan {
	private:
		WifiNetworkList networks_;
		WifiNameList network_names_;
	public:
		Scan();
		const WifiNameList& network_names() const;
		const WifiNetworkList& networks() const;
	};
};