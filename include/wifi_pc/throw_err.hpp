#pragma once

#include <string>

class ThrowError {
private:
public:
	static void WifiAdapterNotFound();
	static void WifiAdapterNotFound(std::string& msg);
};