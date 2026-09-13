#include <iostream>
#include <memory>
#include <wifi_pc.hpp>

int main() {

	// Scannning all nearby wifi networks
	wifi_pc::Scan scan_result;
	// Obtaining scanned network name list
	auto network_names = scan_result.network_names();

	// Printing names of scanned wifi
	for (int i = 0; i < network_names->size(); i++) {

		std::cout << network_names->at(i) << std::endl;
	}
}