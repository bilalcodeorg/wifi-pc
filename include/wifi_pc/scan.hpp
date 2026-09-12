#pragma once

#include <windows.h>
#include <wlanapi.h>
#include <iostream>
#include <string>

#pragma comment(lib, "wlanapi.lib")

std::string WideToStr(const WCHAR* wide) {
    int len = WideCharToMultiByte(CP_UTF8, 0, wide, -1, nullptr, 0, nullptr, nullptr);
    std::string str(len, 0);
    WideCharToMultiByte(CP_UTF8, 0, wide, -1, &str[0], len, nullptr, nullptr);
    return str;
}

int main() {
    HANDLE hClient = nullptr;
    DWORD dwMaxClient = 2;
    DWORD dwCurVersion = 0;
    DWORD dwResult = WlanOpenHandle(dwMaxClient, nullptr, &dwCurVersion, &hClient);
    if (dwResult != ERROR_SUCCESS) {
        std::cerr << "WlanOpenHandle failed: " << dwResult << "\n";
        return 1;
    }

    PWLAN_INTERFACE_INFO_LIST pIfList = nullptr;
    dwResult = WlanEnumInterfaces(hClient, nullptr, &pIfList);
    if (dwResult != ERROR_SUCCESS) {
        std::cerr << "WlanEnumInterfaces failed: " << dwResult << "\n";
        WlanCloseHandle(hClient, nullptr);
        return 1;
    }

    for (DWORD i = 0; i < pIfList->dwNumberOfItems; i++) {
        WLAN_INTERFACE_INFO ifInfo = pIfList->InterfaceInfo[i];
        std::wcout << L"Interface: " << ifInfo.strInterfaceDescription << L"\n";

        // Trigger a scan (async, results may take a second or two)
        WlanScan(hClient, &ifInfo.InterfaceGuid, nullptr, nullptr, nullptr);
        Sleep(3000); // crude wait; better to handle WLAN_NOTIFICATION_ACM_SCAN_COMPLETE

        PWLAN_AVAILABLE_NETWORK_LIST pNetList = nullptr;
        dwResult = WlanGetAvailableNetworkList(
            hClient, &ifInfo.InterfaceGuid,
            WLAN_AVAILABLE_NETWORK_INCLUDE_ALL_ADHOC_PROFILES,