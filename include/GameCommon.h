#pragma once

#include <chrono>

#include "MenticsCommon.h"
#include "NetworkBase.h"
#include "Scheduler.h"

namespace mentics { namespace game {

namespace sched = mentics::scheduler;
namespace cmn = mentics::common;
namespace net = mentics::network;
using boost::asio::ip::udp;

typedef uint32_t ClientIdType;
typedef uint64_t TimeOfType;
typedef uint16_t GameIdType;

const ClientIdType INVALID_CLIENT_ID = 10000000;

struct ClientInfo {
	ClientIdType id;
	udp::endpoint clientEndpoint;

	ClientInfo() : id(INVALID_CLIENT_ID), clientEndpoint(net::NULL_ENDPOINT) {}
	ClientInfo(ClientIdType clientId, udp::endpoint& target) : id(clientId), clientEndpoint(target) {}
};

struct GameInfo {
	GameIdType gameId;


	GameInfo(GameIdType gameId) : gameId(gameId) {}

	template<typename Archive>
	void serialize(Archive& ar) {
		ar(gameId);
	}
};

struct LocalTimeProvider : public sched::SchedulerTimeProvider<TimeOfType> {
	TimeOfType maxTimeAhead() {
		return 2000;
	}

	TimeOfType realTimeUntil(TimeOfType t) {
		return t - cmn::currentTimeMillis();
	}
};

}}