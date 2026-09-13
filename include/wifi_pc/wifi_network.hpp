#pragma once

#include <string>

namespace wifi_pc {
	class WifiNetwork {
	private:
		std::string ssid_;
		int signal_quality_;
		bool is_secured_;

	public:
		WifiNetwork(std::string ssid, int signal_quality, bool is_secured);
		const bool& IsSecured() const;
		const std::string& name() const;
		const int& signal_quality() const;
	};
}