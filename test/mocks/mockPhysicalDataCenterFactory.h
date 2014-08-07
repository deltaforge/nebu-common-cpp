#ifndef NEBUTEST_MOCKPHYSICALDATACENTERFACTORY_H_
#define NEBUTEST_MOCKPHYSICALDATACENTERFACTORY_H_

#include "gmock/gmock.h"

#include "nebu/topology/physicalDataCenterFactory.h"

namespace nebu
{
	namespace test
	{

		class MockPhysicalDataCenterFactory : public nebu::common::PhysicalDataCenterFactory
		{
		public:
			MockPhysicalDataCenterFactory() : PhysicalDataCenterFactory() { };
//			virtual ~MockPhysicalDataCenterFactory() { };

			MOCK_CONST_METHOD1(parseXML, nebu::common::Traits<nebu::common::PhysicalDataCenter>::Ptr(const	tinyxml2::XMLElement *elem));

		private:
		};

	}
}

#endif

