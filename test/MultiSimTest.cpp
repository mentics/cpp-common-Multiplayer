#include "stdafx.h"
#include "CppUnitTest.h"

#include <thread>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

#include "MenticsCommon.h"
#include "GameServer.h"
#include "GameClient.h"


namespace mentics { namespace game {

using namespace std;

TEST_CLASS(MultiSimTest)
{
public:
	TEST_CLASS_INITIALIZE(BeforeClass) {
		auto sink = boost::log::add_file_log("unit-test.log");
		sink->locked_backend()->auto_flush(true);
		boost::log::core::get()->set_filter
		(
			boost::log::trivial::severity >= boost::log::trivial::trace
		);
		boost::log::add_common_attributes();
	}

	static const int MAX_CLIENTS = 100;

	int numClients;
	GameServer<TimeOfType>* server;
	thread* serverThread;
	array<GameClient<TimeOfType>*, MAX_CLIENTS> clients;
	array<thread*, MAX_CLIENTS> threads;

	TEST_METHOD_INITIALIZE(before) {
	}

	TEST_METHOD_CLEANUP(after) {
		destroyClients();
		destroyServer();
	}

	void createServer() {
		server = new GameServer<TimeOfType>(1111);
		serverThread = new thread(&GameServer<TimeOfType>::start, server);
	}

	void destroyServer() {
		server->stop();
		serverThread->join();
		delete server;
		delete serverThread;
	}

	void createClients(int num) {
		numClients = num;
		for (int i = 0; i < numClients; i++) {
			clients[i] = new GameClient<TimeOfType>(cmn::toString(i), "localhost", 1111);
			threads[i] = new thread(&GameClient<TimeOfType>::start, clients[i]);
		}
	}

	void destroyClients() {
		for (int i = 0; i < numClients; i++) {
			clients[i]->stop();
		}
		for (int i = 0; i < numClients; i++) {
			threads[i]->join();
			delete clients[i];
			delete threads[i];
		}
	}


	TEST_METHOD(TestMultiSim)
	{
		createServer();
		createClients(2);
		BOOST_LOG_SEV(server->lg, boost::log::trivial::trace) << "testing server stuff ";

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
};


}}