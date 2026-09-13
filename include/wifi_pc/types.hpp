#pragma once

#include <wifi_pc/wifi_network.hpp>
#include <memory>
#include <vector>


namespace wifi_pc::type {

    typedef std::unique_ptr<std::vector<std::string>> StringList;

	typedef std::vector<std::unique_ptr<wifi_pc::WifiNetwork>> WifiNetList;
}