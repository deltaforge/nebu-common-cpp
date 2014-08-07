#ifndef NEBUTEST_MOCKPHYSICALLOCALSTOREFACTORY_H_
#define NEBUTEST_MOCKPHYSICALLOCALSTOREFACTORY_H_

#include "gmock/gmock.h"

#include "nebu/topology/physicalLocalStoreFactory.h"

namespace nebu
{
	namespace test
	{

		class MockPhysicalLocalStoreFactory : public nebu::common::PhysicalLocalStoreFactory
		{
		public:
			MockPhysicalLocalStoreFactory() : PhysicalLocalStoreFactory() { };
//			virtual ~MockPhysicalLocalStoreFactory() { };

			MOCK_CONST_METHOD1(parseXML, nebu::common::Traits<nebu::common::PhysicalLocalStore>::Ptr(const	tinyxml2::XMLElement *elem));

		private:
		};

	}
}

#endif

