#include "stdafx.h"

#include <array>
#include "protocol.h"
#include "GameClient.h"

namespace mentics { namespace game {

namespace lvl = boost::log::trivial;
namespace net = mentics::network;

template <typename TimeType>
void GameClient<TimeType>::createGame() {
	LOG(lvl::trace) << "createGame";
	network.createGame(std::bind(&GameClient::gameCreated, this, std::placeholders::_1));
}

template <typename TimeType>
void GameClient<TimeType>::gameCreated(const net::GameInfo& info) {
	LOG(lvl::trace) << "gameCreated";
	joinGame(info.gameId);
}

template <typename TimeType>
void GameClient<TimeType>::joinGame(net::GameIdType gameId) {
	LOG(lvl::trace) << "joinGame";

	// TODO
}

template <typename TimeType>
void GameClient<TimeType>::gameJoined(net::GameInfo& info) {
	LOG(lvl::trace) << "gameJoined";
	// TODO
}

template <typename TimeType>
void GameClient<TimeType>::joinFirstGame() {
	std::vector<net::GameInfo> infos;
	while (infos.empty()) {
		//network.listGames(infos);
		LOG(lvl::trace) << "testing server stuff ";
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	// TODO
}

template class GameClient<uint64_t>;

}}