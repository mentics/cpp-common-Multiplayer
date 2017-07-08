#include "stdafx.h"

#include "GameServer.h"

namespace mentics { namespace game {

template <typename TimeType>
uint16_t GameServer<TimeType>::configureGame(uint16_t numAgents) {
	return 0;
}

template <typename TimeType>
void GameServer<TimeType>::startGame(net::GameIdType gameId) {
	
}

template class GameServer<uint64_t>;

}}