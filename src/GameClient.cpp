#include "stdafx.h"

#include <array>
#include "GameClient.h"

namespace mentics { namespace game {

namespace lvl = boost::log::trivial;
namespace net = mentics::network;

template <typename TimeType>
void GameClient<TimeType>::handle(udp::endpoint& endpoint, const std::string& data) {
	LOG(lvl::trace) << "network handle";
}

template <typename TimeType>
void GameClient<TimeType>::handleError(udp::endpoint& endpoint, const boost::system::error_code& error) {
	LOG(lvl::trace) << "network errorHandle";
}

template <typename TimeType>
void GameClient<TimeType>::start() {
	network.start();
}

template <typename TimeType>
void GameClient<TimeType>::stop() {
	sched.stop();
	network.stop();
}

template <typename TimeType>
void GameClient<TimeType>::createGame() {
	LOG(lvl::trace) << "createGame";
	//network.createGame(std::bind(&GameClient::gameCreated, this, std::placeholders::_1));
}

template <typename TimeType>
void GameClient<TimeType>::gameCreated(const GameInfo& info) {
	LOG(lvl::trace) << "gameCreated";
	joinGame(info.gameId);
}

template <typename TimeType>
void GameClient<TimeType>::joinGame(GameIdType gameId) {
	LOG(lvl::trace) << "joinGame";

	// TODO
}

template <typename TimeType>
void GameClient<TimeType>::gameJoined(GameInfo& info) {
	LOG(lvl::trace) << "gameJoined";
	// TODO
}

template <typename TimeType>
void GameClient<TimeType>::joinFirstGame() {
	std::vector<GameInfo> infos;
	while (infos.empty()) {
		//network.listGames(infos);
		LOG(lvl::trace) << "testing server stuff ";
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	// TODO
}

template class GameClient<uint64_t>;

}}