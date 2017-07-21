#include "stdafx.h"

#include <array>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "GameClient.h"

namespace mentics { namespace game {

namespace ptime = boost::posix_time;
namespace lvl = boost::log::trivial;
namespace net = mentics::network;
namespace cmn = mentics::common;

struct GameMessage {
	MessageType msgType;
	ClientIdType clientId;
	std::string data;
};

template <typename TimeType>
bool GameClient<TimeType>::handle(udp::endpoint& endpoint, net::MsgIdType msgId, const std::string& data) {
	LOG(lvl::trace) << "network handle";
	MessageType msgType;
	deserialize(msgType, data);
	std::string payload = data.substr(sizeof(msgType));
	switch (msgType) {
	case GetId: {
		deserialize(clientId, payload);
		LOG(lvl::info) << "GetId received clientId=" << clientId;
		break;
	}
	case CreateGame: {
		deserialize(gameInfo, payload);
		LOG(lvl::info) << "CreateGame received gameInfo=" << gameInfo;
		break;
	}
	case JoinGame: {
		deserialize(gameState, payload);
		LOG(lvl::info) << "JoinGame received gameInfo=" << gameState;
		break;
	}
	}
	if (handler != nullptr) {
		handler(data);
	}
	return true;
}

template <typename TimeType>
void GameClient<TimeType>::handleError(udp::endpoint& endpoint, const boost::system::error_code& error) {
	LOG(lvl::trace) << "handling error " << error << " for endpoint " << endpoint;
	// TODO
}

template <typename TimeType>
void GameClient<TimeType>::start() {
	network.start();
	//sched.start();
}

template <typename TimeType>
void GameClient<TimeType>::stop() {
	sched.stop();
	network.stop();
}

template <typename TimeType>
void GameClient<TimeType>::getId() {
	LOG(lvl::trace) << "getId";
	network.submit(ptime::milliseconds(500), 10, serialize(MessageType::GetId), nullptr);
}

template <typename TimeType>
void GameClient<TimeType>::createGame(const GameParams& params) {
	LOG(lvl::trace) << "createGame";
	send(MessageType::CreateGame, serialize(params), nullptr);
}

template <typename TimeType>
void GameClient<TimeType>::joinGame(const GameJoinParams& params) {
	LOG(lvl::trace) << "joinGame";
	send(MessageType::JoinGame, serialize(params), nullptr);
}

template <typename TimeType>
void GameClient<TimeType>::send(MessageType msgType, std::string data,
		net::MessageCallbackType callback) {
	// NOTE: optimize
	std::string full = serialize(msgType) + serialize(clientId) + data;
	network.submit(ptime::milliseconds(250), 10, full, callback);
}

template class GameClient<uint64_t>;

}}