#ifndef NEBUTEST_MOCKPHYSICALNETWORKSTOREFACTORY_H_
#define NEBUTEST_MOCKPHYSICALNETWORKSTOREFACTORY_H_

#include "gmock/gmock.h"

#include "nebu/topology/physicalNetworkStoreFactory.h"

namespace nebu
{
	namespace test
	{

		class MockPhysicalNetworkStoreFactory : public nebu::common::PhysicalNetworkStoreFactory
		{
		public:
			MockPhysicalNetworkStoreFactory() : PhysicalNetworkStoreFactory() { };
//			virtual ~MockPhysicalNetworkStoreFactory() { };

			MOCK_CONST_METHOD1(parseXML, nebu::common::Traits<nebu::common::PhysicalNetworkStore>::Ptr(const	tinyxml2::XMLElement *elem));

		private:
		};

	}
}

#endif

