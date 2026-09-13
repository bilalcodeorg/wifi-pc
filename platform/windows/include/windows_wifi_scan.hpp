#pragma once

#ifndef WIFI_PC_WINDOWS_WIFI_SCAN_H
#define WIFI_PC_WINDOWS_WIFI_SCAN_H
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
		static std::unique_ptr<wifi_pc::type::WifiNetList> ScanNetworks();
	};
}

#endif // _WIN32
#endif // !WIFI_PC_WINDOWS_WIFI_SCAN_H