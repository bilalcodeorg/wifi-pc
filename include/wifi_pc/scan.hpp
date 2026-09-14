#pragma once

#include <vector>
#include <string>
#include <memory>
#include <wifi_pc/types.hpp>
#include <wifi_pc/wifi_network.hpp>

namespace wifi_pc {
	class Scan {
	private:
		wifi_pc::type::WifiNetList networks_;
	public:
		Scan();
		const wifi_pc::type::StringList network_names() const;
		const wifi_pc::type::WifiNetList& networks() const;
	};
};