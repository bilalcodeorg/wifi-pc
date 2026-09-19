#pragma once

#ifndef WPC_WINDOWS_WIFI_SCAN_H
#define WPC_WINDOWS_WIFI_SCAN_H
#ifdef _WIN32

#include <windows.h>
#include <wlanapi.h>
#include <vector>
#include <string>
#include <wifi_pc/types.hpp>

namespace windows{

	class Wifi {
	private:
		static std::string WideToStr(const WCHAR* wide);
	public:
		static void ScanNetworks(wpc::WifiNetworkList& networks);
	};
}

#endif // _WIN32
#endif // !WPC_WINDOWS_WIFI_SCAN_H