#include <wifi_pc_c_api.h>
#include <iostream>

int main() {
	auto scan = wpc_scan_new();
	auto nets = wpc_scan_networks(scan);

	for (int i = 0; i < wpc_wifi_networks_size(nets); i++) {
		auto network = wpc_wifi_networks_at(nets, i);

		std::cout<<"Name: "<<wpc_wifi_network_name(network)<<" | ";
		std::cout<<"Signal: "<<wpc_wifi_network_signal_quality(
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