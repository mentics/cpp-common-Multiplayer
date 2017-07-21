#include "stdafx.h"

#include <boost/date_time/posix_time/posix_time.hpp>
#include "GameCommon.h"
#include "GameServer.h"
#include "MenticsCommon.h"

namespace mentics { namespace game {

namespace ptime = boost::posix_time;
namespace net = mentics::network;

template <typename TimeType>
void GameServer<TimeType>::start() {
	network.start();
}

template <typename TimeType>
bool GameServer<TimeType>::handle(udp::endpoint& endpoint, net::MsgIdType msgId, const std::string& data) {
	MessageType msgType;
	deserialize(msgType, data);
	ClientIdType clientId;
	size_t offset = sizeof(MessageType);
	if (data.length() > offset) {
		deserialize(clientId, data.substr(offset));
		offset += sizeof(ClientIdType);
	}
	std::string payload = data.substr(offset);
	switch (msgType) {
	case GetId: {
		ClientIdType newClientId = nextClientId;
		nextClientId++;
		clients.emplace_back(newClientId, endpoint);
		std::string out = serialize(MessageType::GetId) + serialize(newClientId);
		LOG(lvl::info) << "handled GetId " << newClientId;
		network.submitReply(endpoint, ptime::milliseconds(250), 8, out, nullptr, msgId);
		return false;
	}
	case CreateGame: {
		GameIdType newGameId = nextGameId;
		nextGameId++;
		GameParams params;
		deserialize(params, payload);
		GameInfo info = { newGameId, params };
		std::string out = serialize(MessageType::CreateGame) + serialize(info);
		LOG(lvl::info) << "handled CreateGame " << newGameId;
		network.submitReply(endpoint, ptime::milliseconds(250), 8, out, nullptr, msgId);
		return false;
	}
	case JoinGame: {
		GameJoinParams params;
		deserialize(params, payload);
		GameState state = { params.id };
		std::string out = serialize(MessageType::JoinGame) + serialize(state);
		LOG(lvl::info) << "handled JoinGame " << params.id;
		network.submitReply(endpoint, ptime::milliseconds(250), 8, out, nullptr, msgId);
		return false;
	}
	}
	LOG(lvl::warning) << "network handled unsupported message type " << msgType;
	return true;
}

template <typename TimeType>
void GameServer<TimeType>::handleError(udp::endpoint& endpoint, const boost::system::error_code& error) {
	LOG(lvl::trace) << "network errorHandle";
	// TODO
}

template <typename TimeType>
void GameServer<TimeType>::stop() {
	network.stop();
}


template class GameServer<uint64_t>;

}}