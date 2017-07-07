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

	void stop() {
		network.stop();
	}
};

}}