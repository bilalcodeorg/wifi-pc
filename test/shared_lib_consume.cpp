#include <wifi_pc_c_api.h>
#include <iostream>

int main() {
	auto scan = wifi_pc_scan_new();
	auto nets = wifi_pc_scan_networks(scan);

	for (int i = 0; i < wifi_pc_wifi_networks_size(nets); i++) {
		auto network = wifi_pc_wifi_networks_at(nets, i);

		std::cout<<"Name: "<<wifi_pc_wifi_network_name(network)<<" | ";
		std::cout<<"Signal: "<<wifi_pc_wifi_network_signal_quality(
			network
		)<<" | ";	
		std::cout<<"Security: "<<(
			wifi_pc_wifi_network_is_secured(network)
				? "Secured" : "Not secured!"
		)<<std::endl;
	}
	
	std::cin.get();
	return 0;
}