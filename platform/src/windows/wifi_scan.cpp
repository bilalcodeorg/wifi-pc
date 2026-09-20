#include <windows/wifi_scan.hpp>

#ifdef _WIN32

#include <windows.h>
#include <wlanapi.h>
#include <vector>
#include <string>
#include <memory>
#include <wifi_pc/throw_err.hpp>
#include <wifi_pc/wifi_network.hpp>
#include <wifi_pc/types.hpp>

std::string windows::Wifi::WideToStr(const WCHAR* wide) {
    int len = WideCharToMultiByte(CP_UTF8, 0, wide, -1, nullptr, 0,
        nullptr, nullptr);
    std::string str(len, 0);
    WideCharToMultiByte(CP_UTF8, 0, wide, -1, &str[0], len, nullptr, nullptr);
    return str;
}

// Scanned wifi networks will be stored in networks paramter
// of function
void windows::Wifi::ScanNetworks(wpc::WifiNetworkList& networks)
{

    HANDLE hClient = nullptr;
    DWORD dwMaxClient = 2;
    DWORD dwCurVersion = 0;
    DWORD dwResult = WlanOpenHandle(dwMaxClient, nullptr,
        &dwCurVersion, &hClient);

    // Target (interface) adapter index
    const int target_interface_index = 0;

    if (dwResult != ERROR_SUCCESS) {
        //std::cerr << "WlanOpenHandle failed: " << dwResult << "\n";
        wpc::ThrowError::OsError(
            "windows: WlanOpenHandle failed: " + dwResult
        );
        //return 1;
    }

    PWLAN_INTERFACE_INFO_LIST pIfList = nullptr;
    dwResult = WlanEnumInterfaces(hClient, nullptr, &pIfList);
    if (dwResult != ERROR_SUCCESS) {
        //std::cerr << "WlanEnumInterfaces failed: " << dwResult << "\n";
        WlanCloseHandle(hClient, nullptr);
        wpc::ThrowError::OsError(
            "windows: WlanEnumInterfaces failed: " + dwResult
        );
        //return 1;
    }

    if (!pIfList->dwNumberOfItems) {
        wpc::ThrowError::NoAdapter("no adapter found");
    }

    WLAN_INTERFACE_INFO ifInfo = pIfList->InterfaceInfo[
        target_interface_index
    ];
    //std::wcout << L"Interface: " << ifInfo.strInterfaceDescription << L"\n";

    // Trigger a scan (async, results may take a second or two)
    WlanScan(hClient, &ifInfo.InterfaceGuid, nullptr, nullptr, nullptr);
    // crude wait; better to handle WLAN_NOTIFICATION_ACM_SCAN_COMPLETE
    Sleep(3000);

    PWLAN_AVAILABLE_NETWORK_LIST pNetList = nullptr;
    dwResult = WlanGetAvailableNetworkList(
        hClient, &ifInfo.InterfaceGuid,
        WLAN_AVAILABLE_NETWORK_INCLUDE_ALL_ADHOC_PROFILES,
        nullptr, &pNetList);

    if (dwResult == ERROR_SUCCESS) {
        for (DWORD j = 0; j < pNetList->dwNumberOfItems; j++) {
            WLAN_AVAILABLE_NETWORK net = pNetList->Network[j];
            std::string ssid(
                (char*)net.dot11Ssid.ucSSID, net.dot11Ssid.uSSIDLength
            );

            {
                wpc::WifiNetwork network(
                    ssid, net.wlanSignalQuality,
                    net.bSecurityEnabled ? true : false
                );

                networks.push_back(std::move(network));
            }
        }
        WlanFreeMemory(pNetList);
    }
    else {
        wpc::ThrowError::OsError(
            "windows: WlanGetAvailableNetworkList failed: " + dwResult
        );
        //std::cerr << "  WlanGetAvailableNetworkList failed: " << dwResult << "\n";
    }


    WlanFreeMemory(pIfList);
    WlanCloseHandle(hClient, nullptr);
}

#endif // _WIN32