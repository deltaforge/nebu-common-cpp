
#ifndef NEBUTEST_MOCKAPPVIRTREQUEST_H_
#define NEBUTEST_MOCKAPPVIRTREQUEST_H_

#include "nebu/appVirtRequest.h"

#include "gmock/gmock.h"

namespace nebu
{
	namespace test
	{

		class MockAppVirtRequest : public nebu::common::AppVirtRequest
		{
		public:
			MockAppVirtRequest() : nebu::common::AppVirtRequest(std::shared_ptr<nebu::common::NebuClient>(), "") { }
			virtual ~MockAppVirtRequest() { }

			MOCK_CONST_METHOD1(getVirtualMachine, nebu::common::VirtualMachine(const std::string &uuid));
			MOCK_CONST_METHOD0(getVirtualMachineIDs, std::vector<std::string>());
		};

	}
}

#endif
