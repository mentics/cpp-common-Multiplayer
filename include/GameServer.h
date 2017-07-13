#pragma once

#include "NetworkServer.h"
#include "MenticsCommon.h"

namespace mentics { namespace game {

namespace lvl = boost::log::trivial;
using boost::asio::ip::udp;
namespace cmn = mentics::common;
namespace net = mentics::network;

template <typename TimeType>
class GameServer : public cmn::CanLog, net::NetworkHandler {
private:
	net::NetworkServer network;

public:
	GameServer(uint16_t localport) : CanLog("GameServer"),
		network(localport, this) {}

	void start() {
		network.start();
	}

	void handle(udp::endpoint& endpoint, const std::string& data) override {
		LOG(lvl::trace) << "network handle";
	}
	void handleError(udp::endpoint& endpoint, const boost::system::error_code& error) override {
		LOG(lvl::trace) << "network errorHandle";
	}


	//uint16_t configureGame(uint16_t numAgents);
	//void startGame(uint16_t gameId);

	void stop() {
		network.stop();
	}
};

}}