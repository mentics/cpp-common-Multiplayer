#pragma once

#include "NetworkClient.h"
#include "Scheduler.h"
#include "GameCommon.h"

namespace mentics { namespace game {

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
class GameClient : public cmn::CanLog {
private:
	net::NetworkClient network;
	LocalTimeProvider timeProvider;
	sched::SchedulerModel<TimeType> model;
	sched::Scheduler<TimeType> sched;
	std::vector<Agent*> agents;

public:
	GameClient(std::string name, std::string hostname, uint16_t serverPort) : CanLog("GameClient"+name),
		network(hostname, serverPort),
		model("Model" + name), timeProvider(),
		sched("Scheduler" + name, &model, &timeProvider) {}

	void start() {
		network.start();
	}

	void createGame();
	void gameCreated(const net::GameInfo& info);
	void joinFirstGame();
	void joinGame(net::GameIdType gameId);
	void gameJoined(net::GameInfo& info);

	//void createPlayerAgent(); // TODO: add param for input interface
	//void createBotAgent(); // TODO: pass in any type info
	//void createRemoteAgent(); // TODO: pass in remote id or whatever

	void stop() {
		sched.stop();
		network.stop();
	}
};

}}