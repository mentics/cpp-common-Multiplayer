#include "stdafx.h"

#include "MenticsCommon.h"
#include "GameServer.h"

namespace mentics { namespace game {

//template <typename TimeType>
//uint16_t GameServer<TimeType>::configureGame(uint16_t numAgents) {
//	return 0;
//}
//
//template <typename TimeType>
//void GameServer<TimeType>::startGame(net::GameIdType gameId) {
//	
//}

template <typename TimeType>
void GameServer<TimeType>::
	start() {
	network.start();
}

template <typename TimeType>
void GameServer<TimeType>::handle(udp::endpoint& endpoint, const std::string& data) {
	LOG(lvl::trace) << "network handle";
}

template <typename TimeType>
void GameServer<TimeType>::handleError(udp::endpoint& endpoint, const boost::system::error_code& error) {
	LOG(lvl::trace) << "network errorHandle";
}

template <typename TimeType>
void GameServer<TimeType>::stop() {
	network.stop();
}


template class GameServer<uint64_t>;

}}