#pragma once

#include "NetworkServer.h"
#include "MenticsCommon.h"

namespace mentics { namespace game {

namespace cmn = mentics::common;
namespace net = mentics::network;

template <typename TimeType>
class GameServer : public cmn::CanLog {
private:
	net::NetworkServer network;

public:
	GameServer(uint16_t localport) : CanLog("GameServer"),
		network(localport) {}

	void start() {
		network.start();
	}

	uint16_t configureGame(uint16_t numAgents);
	void startGame(uint16_t gameId);

	void stop() {
		network.stop();
	}
};

}}