#ifndef NEBUTEST_MOCKPHYSICALHOST_H_
#define NEBUTEST_MOCKPHYSICALHOST_H_

#include "gmock/gmock.h"

#include "nebu/topology/physicalHost.h"

using nebu::common::PhysicalHost;
using nebu::common::PhysicalRack;

namespace nebu
{
	namespace test
	{

		class MockPhysicalHost : public PhysicalHost
		{
		public:
			MockPhysicalHost() : PhysicalHost("") { };
//			virtual ~MockPhysicalHost() { };

			MOCK_METHOD0(getUUID, std::string());
			MOCK_CONST_METHOD0(getParent, PhysicalRack *());
			MOCK_METHOD1(setParent, void(PhysicalRack *parent));

		private:
		};

	}
}

#endif

