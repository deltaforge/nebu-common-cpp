#ifndef NEBUTEST_MOCKPHYSICALNETWORKSTORE_H_
#define NEBUTEST_MOCKPHYSICALNETWORKSTORE_H_

#include "gmock/gmock.h"

#include "nebu/topology/physicalNetworkStore.h"

using nebu::common::PhysicalNetworkStore;
using nebu::common::PhysicalRack;

namespace nebu
{
	namespace test
	{

		class MockPhysicalNetworkStore : public PhysicalNetworkStore
		{
		public:
			MockPhysicalNetworkStore() : PhysicalNetworkStore("") { };
//			virtual ~MockPhysicalNetworkStore() { };

			MOCK_METHOD0(getUUID, std::string());
			MOCK_CONST_METHOD0(getParent, PhysicalRack *());
			MOCK_METHOD1(setParent, void(PhysicalRack *parent));

		private:
		};

	}
}

#endif

