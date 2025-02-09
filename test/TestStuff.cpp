#include "stdafx.h"
#include "CppUnitTest.h"

#include <thread>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/portable_binary.hpp>
#include "NetworkServer.h"
#include "GameCommon.h"
#include "MenticsCommonTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace mentics { namespace game {

	struct MyClass
	{
		int x, y, z;

		// This method lets cereal know which data members to serialize
		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(x, y, z); // serialize things by passing them to the archive
		}
	};

TEST_CLASS(NetworkTest)
{
public:
	TEST_CLASS_INITIALIZE(BeforeClass) {
		mentics::test::setupLog();
	}

	//TEST_METHOD(TestRetrySend) {
	//	NetworkServer server(1111);
	//	std::thread serverThread(&NetworkServer::start, &server);

	//	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	//	server.testTimer();
	//	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	//	server.stop();
	//	serverThread.join();
	//}

	TEST_METHOD(TestSerialize2) {
		std::stringstream ss; // any stream can be used

		{
			cereal::BinaryOutputArchive oarchive(ss); // Create an output archive

			MyClass m1, m2, m3;
			m1.x = 1345;
			oarchive(m1, m2, m3); // Write the data to the archive
		} // archive goes out of scope, ensuring all contents are flushed

		{
			cereal::BinaryInputArchive iarchive(ss); // Create an input archive

			MyClass m1, m2, m3;
			iarchive(m1, m2, m3); // Read the data from the archive

			Assert::AreEqual(1345, m1.x);
		}
	}

	TEST_METHOD(TestSerialize) {
		GameInfo saveInfo = { (GameIdType)37 };
		GameInfo loadInfo = { (GameIdType)-1 };

		std::string saved = serialize(saveInfo);
		deserialize(loadInfo, saved);

		//std::istringstream is(saved);
		//cereal::BinaryInputArchive iarchive(is);
		//iarchive(loadInfo);

		Assert::AreEqual<int>(37, loadInfo.id);
	}
};

}}