#pragma once

#include "NetworkClient.h"
#include "Scheduler.h"
#include "GameCommon.h"

namespace mentics { namespace game {

namespace lvl = boost::log::trivial;
using boost::asio::ip::udp;
namespace net = mentics::network;
namespace sched = mentics::scheduler;


class Agent : public cmn::CanLog {
public:

};

class PlayerAgent : public Agent {

};

class RemoteAgent : public Agent {

};

class BotAgent : public Agent {

};


template <typename TimeType>
class MakeEvents : public cmn::CanLog {
private:
	sched::Schedulator<TimeType>* sched;
public:
	MakeEvents(sched::Schedulator<TimeType>* sched) : sched(sched) {}
};


template <typename TimeType>
class GameClient : public cmn::CanLog, net::NetworkHandler {
public:
	GameClient(std::string name, const udp::endpoint& endpoint) : CanLog("GameClient"+name),
		network(endpoint, this),
		model("Model" + name), timeProvider(),
		sched("Scheduler" + name, &model, &timeProvider) {}

	void start();
	void stop();

	void getId();
	//void createGame();
	//void joinGame(GameIdType gameId);

	//void createPlayerAgent(); // TODO: add param for input interface
	//void createBotAgent(); // TODO: pass in any type info
	//void createRemoteAgent(); // TODO: pass in remote id or whatever

	bool handle(udp::endpoint& endpoint, net::MsgIdType msgId, const std::string& data) override;
	void handleError(udp::endpoint& endpoint, const boost::system::error_code& error) override;

private:
	ClientIdType id = INVALID_CLIENT_ID;
	net::NetworkClient network;
	LocalTimeProvider timeProvider;
	sched::SchedulerModel<TimeType> model;
	sched::Scheduler<TimeType> sched;
	std::vector<Agent*> agents;
};

}}