#pragma once

#include <string>

namespace wifi_pc {

	class ThrowError {
	private:
	public:
		static void General();
		static void General(const std::string& msg);
		static void WifiAdapterNotFound();
		static void WifiAdapterNotFound(const std::string& msg);
		static void UnsupportedPlatform();
		static void UnsupportedPlatform(const std::string& msg);
	};

};