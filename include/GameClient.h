#pragma once

#include "NetworkClient.h"
#include "Scheduler.h"
#include "GameCommon.h"

namespace mentics { namespace game {

namespace net = mentics::network;
namespace sched = mentics::scheduler;

template <typename TimeType>
class GameClient : public cmn::CanLog {
private:
	net::NetworkClient network;
	sched::SchedulerModel<TimeType> model;
	LocalTimeProvider timeProvider;
	sched::Scheduler<TimeType> sched;

public:
	GameClient(std::string name, std::string hostname, uint16_t serverPort) : CanLog("GameClient"+name),
		network(hostname, serverPort),
		model("Model" + name), timeProvider(),
		sched("Scheduler" + name, &model, &timeProvider) {}

	void start() {
		network.start();
	}

	void stop() {
		sched.stop();
		network.stop();
	}
};

}}