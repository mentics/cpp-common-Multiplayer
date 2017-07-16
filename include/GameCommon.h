#pragma once

#include <chrono>

#include <cereal/archives/binary.hpp>
#include <cereal/archives/portable_binary.hpp>

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

enum MessageType : byte { GetId = 1, CreateGame = 2, JoinGame = 3 };

struct GameInfo {
	GameIdType id;

	GameInfo() {}
	GameInfo(GameIdType gameId) : id(gameId) {}

	template<typename Archive>
	void serialize(Archive& ar) {
		ar(id);
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

template <typename T>
inline std::string serialize(const T& obj) {
	std::stringstream ss;
	cereal::BinaryOutputArchive out(ss);
	out(obj);
	return ss.str();
}

//template <typename T, typename S>
//inline std::string serialize(const T& obj, const S& obj2) {
//	std::stringstream ss;
//	cereal::BinaryOutputArchive out(ss);
//	out(obj, obj2);
//	return ss.str();
//}


template <typename T>
inline void deserialize(T& obj, const std::string& data) {
	std::istringstream is(data);
	cereal::BinaryInputArchive in(is);
	in(obj);
}

}}