#include <wifi_pc/wifi_network.hpp>
#include <string>

wifi_pc::WifiNetwork::WifiNetwork(std::string ssid, int signal_quality, bool is_secured)
	: ssid_(ssid), signal_quality_(signal_quality), is_secured_(is_secured) { }

const bool& wifi_pc::WifiNetwork::IsSecured() const
{
	return this->is_secured_;
}

const std::string& wifi_pc::WifiNetwork::name() const
{
	return this->ssid_;
}

const int& wifi_pc::WifiNetwork::signal_quality() const
{
	return this->signal_quality_;
}