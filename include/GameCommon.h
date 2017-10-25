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

enum GameType : byte { Basic = 1 };

struct GameParams {
	GameType type;

	template<typename Archive>
	void serialize(Archive& ar) {
		ar(type);
	}

	template<typename charT, typename Traits>
	friend std::basic_ostream<charT, Traits>& operator<<(std::basic_ostream<charT, Traits>& os, const GameParams& obj) {
		os << "GameParams { type=" << obj.type << "}";
		return os;
	}
};

struct GameInfo {
	GameIdType id;
	GameParams params;

	template<typename Archive>
	void serialize(Archive& ar) {
		ar(id, params);
	}

	template<typename charT, typename Traits>
	friend std::basic_ostream<charT, Traits>& operator<<(std::basic_ostream<charT, Traits>& os, const GameInfo& obj) {
		os << "GameInfo { id=" << obj.id << ", params=" << obj.params << "}";
		return os;
	}
};

struct GameJoinParams {
	GameIdType id;

	template<typename Archive>
	void serialize(Archive& ar) {
		ar(id);
	}

	template<typename charT, typename Traits>
	friend std::basic_ostream<charT, Traits>& operator<<(std::basic_ostream<charT, Traits>& os, const GameJoinParams& obj) {
		os << "GameJoinParams { id=" << obj.id << "}";
		return os;
	}
};

struct GameState {
	GameIdType id;

	template<typename Archive>
	void serialize(Archive& ar) {
		ar(id);
	}

	template<typename charT, typename Traits>
	friend std::basic_ostream<charT, Traits>& operator<<(std::basic_ostream<charT, Traits>& os, const GameState& obj) {
		os << "GameState { id=" << obj.id << "}";
		return os;
	}
};

// TODO: replace with realtime provider or something
struct LocalTimeProvider : public sched::SchedulerTimeProvider<TimeOfType> {
	TimeOfType maxTimeAhead() {
		return 2000;
	}

	TimeOfType now() {
		return cmn::currentTimeMillis();
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