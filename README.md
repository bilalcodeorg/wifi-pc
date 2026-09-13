# Wifi PC

A small C++ library for scanning nearby WiFi networks and reading their names.

## What it does

`wifi_pc` gives you a simple way to trigger a WiFi scan from your C++ program and get back the list of network names (SSIDs) that were found nearby.

## Requirements

- A C++ compiler with C++11 support or newer
- The `wifi_pc.hpp` header available in your include path

## Installation

Copy the `wifi_pc.hpp` header (and any accompanying source files) into your project, then include it like any other header:

```cpp
#include <wifi_pc.hpp>
```

## Usage

Here's a basic example showing how to scan for nearby networks and print their names:

```cpp
#include <iostream>
#include <wifi_pc.hpp>

int main() {

	// Scanning all nearby wifi networks
	wifi_pc::Scan scan_result;

	// Obtaining scanned network name list
	auto network_names = scan_result.network_names();

	// Printing names of scanned wifi
	for (int i = 0; i < network_names->size(); i++) {

		std::cout << network_names->at(i) << std::endl;
	}
}
```

### How it works

1. Create a `wifi_pc::Scan` object. This triggers a scan of nearby WiFi networks.
2. Call `network_names()` on the scan object to get the list of discovered network names.
3. Loop through the list using `size()` and `at(i)` to access each network name.

## Notes

This project is still early, so the API surface is minimal right now. More features will be added as the library grows.