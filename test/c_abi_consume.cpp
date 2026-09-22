#include <wifi_pc_c_api.h>
#include <iostream>

int main() {
	WpcScan* scan = wpc_scan_new();
	const WpcWifiNetworkList* nets = nullptr;
	size_t networks_count;
	
	if (scan == nullptr) {
		std::cout << "Error code: " << wpc_last_error_code() << "\n";
		std::cout << "Error reason: " << wpc_last_error_reason() << "\n";
		wpc_scan_destroy(scan);
		return 1;
	}

	nets = wpc_scan_networks(scan);
	networks_count = wpc_wifi_network_list_size(nets);
	
	for (int i = 0; i < networks_count; i++) {
		auto network = wpc_wifi_network_list_at(nets, i);

		std::cout<<"Name: "<<wpc_wifi_network_name(network)<<" | ";
		std::cout<<"Signal: "<<(int) wpc_wifi_network_signal_quality(
			network
		)<<" | ";
		std::cout<<"Security: "<<(
			wpc_wifi_network_is_secured(network)
				? "Secured" : "Not secured!"
		)<<std::endl;
	}
	
	wpc_scan_destroy(scan);
	std::cin.get();
	return 0;
}