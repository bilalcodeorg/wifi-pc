#include <wifi_pc/throw_err.hpp>
#include <wifi_pc/error.hpp>
#include <wifi_pc/error_enum.hpp>
#include <string>

void wpc::ThrowError::General() {
	General("something went wrong");
}

void wpc::ThrowError::General(const std::string& msg) {
	throw wpc::Error(wpc::err_code::kGeneral, "Error: " + msg);
}

void wpc::ThrowError::NoAdapter() {
	std::string msg = "failed to initialize Wi-Fi adapter";
	NoAdapter(msg);
}

void wpc::ThrowError::NoAdapter(const std::string& msg) {
	throw wpc::Error(wpc::err_code::kNoAdapter, "NoAdapterError: " + msg);
}

void wpc::ThrowError::UnsupportedPlatform() {
	UnsupportedPlatform("current platform not supported");
}

void wpc::ThrowError::UnsupportedPlatform(const std::string& msg) {
	throw wpc::Error(
		wpc::err_code::kUnsupportedPlatform, "UnsupportedPlatform: " + msg
	);
}
