
#ifndef NEBUTEST_MOCKAPPPHYSREQUEST_H_
#define NEBUTEST_MOCKAPPPHYSREQUEST_H_

#include "nebu/appPhysRequest.h"

#include "gmock/gmock.h"

namespace nebu
{
	namespace test
	{

		class MockAppPhysRequest : public nebu::common::AppPhysRequest
		{
		public:
			MockAppPhysRequest() : AppPhysRequest(std::shared_ptr<nebu::common::NebuClient>(), "") { }
			virtual ~MockAppPhysRequest() { }

			MOCK_CONST_METHOD0(getPhysicalTopology, std::shared_ptr<nebu::common::PhysicalRoot>());

		};

	}
}

#endif
