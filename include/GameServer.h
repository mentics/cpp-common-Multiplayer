#pragma once

#include "NetworkServer.h"
#include "MenticsCommon.h"

namespace mentics { namespace game {

namespace com = mentics::common;
namespace net = mentics::network;

class GameServer : public common::CanLog {
private:
	net::NetworkServer network;

public:
	//static GameServer createGameServer();

	GameServer(uint16_t localport) : network(localport) {}

	void start() {
		network.start();
	}

	void stop() {
		network.stop();
	}
};

}}