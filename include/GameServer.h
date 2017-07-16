#pragma once

#include <vector>
#include "MenticsCommon.h"
#include "NetworkServer.h"
#include "GameCommon.h"

namespace mentics { namespace game {

namespace lvl = boost::log::trivial;
using boost::asio::ip::udp;
namespace cmn = mentics::common;
namespace net = mentics::network;

template <typename TimeType>
class GameServer : public cmn::CanLog, net::NetworkHandler {
public:
	GameServer(uint16_t localport) : CanLog("GameServer"),
		nextClientId(1),
		network(localport, this) {}

	void start();

	bool handle(udp::endpoint& endpoint, net::MsgIdType msgId, const std::string& data) override;
	void handleError(udp::endpoint& endpoint, const boost::system::error_code& error) override;

	//uint16_t configureGame(uint16_t numAgents);
	//void startGame(uint16_t gameId);

	void stop();

private:
	ClientIdType nextClientId;
	net::NetworkServer network;
	std::vector<ClientInfo> clients;
};

}}