#include <wifi_pc_c_api.h>
#include <iostream>

int main() {
	WpcScan* scan = nullptr;
	const WpcWifiNetworkList* nets = nullptr;
	WpcCode result = wpc_scan_new(scan);
	
	if (result != kWpcSuccess) {
		std::cout << "Error occured";
		wpc_scan_destroy(scan);
		return 1;
	}

	nets = wpc_scan_networks(scan);
	
	for (int i = 0; i < wpc_wifi_network_list_size(nets); i++) {
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
	
	std::cin.get();
	return 0;
}