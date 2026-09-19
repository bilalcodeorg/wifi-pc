#include <iostream>
#include <wifi_pc.hpp>

int main() {

	// Scannning all nearby wifi networks
	wpc::Scan scan_result;
	
	// Obtaining scanned network name list
	wpc::WifiNameList network_names = scan_result.network_names();

	// Printing names of scanned wifi
	for (int i = 0; i < network_names.size(); i++) {

		std::cout << network_names[i] << std::endl;
	}

	return 0;
}