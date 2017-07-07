#pragma once

#include "NetworkClient.h"

namespace mentics { namespace game {

namespace net = mentics::network;

class GameClient {
private:
	net::NetworkClient network;

public:
	GameClient(std::string hostname, uint16_t serverPort) : network(hostname, serverPort) {}

	void start() {
		network.start();
	}

	void stop() {
		network.stop();
	}
};

}}