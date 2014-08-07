
#ifndef NEBUTEST_MOCKNEBUCLIENT_H_
#define NEBUTEST_MOCKNEBUCLIENT_H_

#include "gmock/gmock.h"

#include "nebu/nebuClient.h"

namespace nebu
{
	namespace test
	{

		class MockNebuClient : public nebu::common::NebuClient
		{
		public:
			MockNebuClient() : NebuClient(std::shared_ptr<nebu::common::RestClientAdapter>(), "") { }
			virtual ~MockNebuClient() { }

			MOCK_CONST_METHOD1(performGET, NebuClient::Response(const std::string& URI));
		};

	}
}

#endif
