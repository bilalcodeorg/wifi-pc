#pragma once

#include <string>

namespace wifi_pc {

	class ThrowError {
	private:
	public:
		static void WifiAdapterNotFound();
		static void WifiAdapterNotFound(const std::string& msg);
	};

};