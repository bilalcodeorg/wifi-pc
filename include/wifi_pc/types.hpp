#pragma once

#include <wifi_pc/wifi_network.hpp>
#include <memory>
#include <vector>


namespace wpc {
	namespace type {

		typedef std::vector<std::string> WifiNames;
		typedef std::vector<wpc::WifiNetwork> WifiNetworks;
	};
};