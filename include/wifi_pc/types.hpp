#pragma once

#include <wifi_pc/wifi_network.hpp>
#include <memory>
#include <vector>


namespace wpc {
	typedef std::vector<std::string> WifiNameList;
	typedef std::vector<wpc::WifiNetwork> WifiNetworkList;
};