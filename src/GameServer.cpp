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
	LOG(lvl::trace) << "network handle";
	MessageType msgType;
	deserialize(msgType, data);
	switch (msgType) {
	case GetId:
		clients.emplace_back(nextClientId++, endpoint);
		std::string out = serialize(MessageType::GetId) + serialize(nextClientId - 1);
		network.submitReply(endpoint, ptime::milliseconds(250), 4,
			out, nullptr, msgId);
		return false;
	}
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