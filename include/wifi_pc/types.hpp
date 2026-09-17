#pragma once

#include <wifi_pc/wifi_network.hpp>
#include <memory>
#include <vector>


namespace wifi_pc::type {
	typedef std::vector<std::string> WifiNames;
	typedef std::vector<wifi_pc::WifiNetwork> WifiNetworks;
}