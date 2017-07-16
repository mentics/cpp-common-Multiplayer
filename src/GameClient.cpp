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
	switch (msgType) {
	case GetId:
		// TODO: fix this
		std::string data2 = data.substr(sizeof(msgType));
		ClientIdType clientId;
		deserialize(clientId, data2);
		LOG(lvl::info) << "Received clientId=" << clientId;
		break;
	}
	return true;
}

template <typename TimeType>
void GameClient<TimeType>::handleError(udp::endpoint& endpoint, const boost::system::error_code& error) {
	LOG(lvl::trace) << "network errorHandle";
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
	network.submit(ptime::milliseconds(500), 10, serialize(MessageType::GetId), [this](const udp::endpoint& endpoint, const std::string& data) {
		deserialize(this->id, data);
		LOG(lvl::info) << "Client was assigned clientId=" + this->id;
	});
}

//template <typename TimeType>
//void GameClient<TimeType>::createGame() {
//	LOG(lvl::trace) << "createGame";
//	std::string data;
//	data += MessageType::CreateGame; // TODO: simplify
//	network.submit(ptime::seconds(1), 10, data, [this](const udp::endpoint& endpoint, const std::string& data) {
//		GameInfo info;
//		deserialize(info, data);
//		LOG(lvl::info) << "Client created game id=" + info.id;
//	});
//}
//
//template <typename TimeType>
//void GameClient<TimeType>::joinGame(GameIdType gameId) {
//	LOG(lvl::trace) << "joinGame";
//	std::string data;
//	data += MessageType::JoinGame;
//	data += boost::lexical_cast<std::string>(gameId);
//	network.submit(ptime::seconds(1), 10, data, [this](const udp::endpoint& endpoint, const std::string& data) {
//		GameInfo info;
//		deserialize(info, data);
//		LOG(lvl::info) << "Client created game id=" + info.id;
//	});
//}

template class GameClient<uint64_t>;

}}