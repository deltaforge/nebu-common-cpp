#ifndef NEBUTEST_MOCKPHYSICALRACKFACTORY_H_
#define NEBUTEST_MOCKPHYSICALRACKFACTORY_H_

#include "gmock/gmock.h"

#include "nebu/topology/physicalRackFactory.h"

namespace nebu
{
	namespace test
	{

		class MockPhysicalRackFactory : public nebu::common::PhysicalRackFactory
		{
		public:
			MockPhysicalRackFactory() : PhysicalRackFactory() { };
//			virtual ~MockPhysicalRackFactory() { };

			MOCK_CONST_METHOD1(parseXML, nebu::common::Traits<nebu::common::PhysicalRack>::Ptr(const	tinyxml2::XMLElement *elem));

		private:
		};

	}
}

#endif

