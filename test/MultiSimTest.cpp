#include "stdafx.h"
#include "CppUnitTest.h"

#include <thread>
#include <future>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "MenticsCommon.h"
#include "GameServer.h"
#include "GameClient.h"
#include "MenticsCommonTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace mentics { namespace game {

namespace ptime = boost::posix_time;
namespace net = mentics::network;

TEST_CLASS(MultiSimTest)
{
public:
	TEST_CLASS_INITIALIZE(BeforeClass) {
		mentics::test::setupLog();
	}

	TEST_METHOD_INITIALIZE(before) {
	}

	TEST_METHOD_CLEANUP(after) {
	}

	TEST_METHOD(TestMultiSim) {
		const int numClients = 1;

		GameServer<TimeOfType> server(1111);
		//std::thread serverThread = std::thread(&GameServer<TimeOfType>::start, &server);
		server.start();

		std::vector<GameClient<TimeOfType>*> clients;
		//std::vector<std::thread*> clientThreads;
		for (int i = 0; i < numClients; i++) {
			GameClient<TimeOfType>* c = new GameClient<TimeOfType>("GameClient" + boost::lexical_cast<std::string>(i),
				net::NetworkClient::endpointFor("localhost", 1111));
			clients.push_back(c);
			c->start();
			//std::thread* clientThread = new std::thread(&GameClient<TimeOfType>::start, c);
			//clientThreads.push_back(clientThread);
		}

		std::promise<std::string> promise;
		clients[0]->handler = [&promise](const std::string& data) {
			promise.set_value(data);
		};
		std::string result;

		clients[0]->getId();
		result = promise.get_future().get();
		promise = std::promise<std::string>();
		Assert::AreEqual((ClientIdType)1, clients[0]->clientId, L"", LINE_INFO());

		clients[0]->createGame(GameParams() = { GameType::Basic });
		result = promise.get_future().get();
		promise = std::promise<std::string>();
		Assert::AreEqual((uint32_t)1, (uint32_t)clients[0]->gameInfo.id, L"", LINE_INFO());

		clients[0]->joinGame(GameJoinParams() = { 1 });
		result = promise.get_future().get();
		promise = std::promise<std::string>();
		Assert::AreEqual((uint32_t)1, (uint32_t)clients[0]->gameInfo.id, L"", LINE_INFO());

		for (int i = 0; i < numClients; i++) {
			clients[i]->stop();
			//clientThreads[i]->join();
			delete clients[i];
			//delete clientThreads[i];
		}

		server.stop();
		//serverThread.join();
	}
};


}}