#pragma once

#include <string>

namespace wpc {

	class ThrowError {
	private:
	public:
		static void General();
		static void General(const std::string& msg);
		static void NoAdapter();
		static void NoAdapter(const std::string& msg);
		static void UnsupportedPlatform();
		static void UnsupportedPlatform(const std::string& msg);
	};

};