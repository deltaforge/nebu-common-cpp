#ifndef NEBUTEST_MOCKPHYSICALHOSTFACTORY_H_
#define NEBUTEST_MOCKPHYSICALHOSTFACTORY_H_

#include "gmock/gmock.h"

#include "nebu/topology/physicalHostFactory.h"

namespace nebu
{
	namespace test
	{

		class MockPhysicalHostFactory : public nebu::common::PhysicalHostFactory
		{
		public:
			MockPhysicalHostFactory() : PhysicalHostFactory() { };
//			virtual ~MockPhysicalHostFactory() { };

			MOCK_CONST_METHOD1(parseXML, nebu::common::Traits<nebu::common::PhysicalHost>::Ptr(const	tinyxml2::XMLElement *elem));

		private:
		};

	}
}

#endif

