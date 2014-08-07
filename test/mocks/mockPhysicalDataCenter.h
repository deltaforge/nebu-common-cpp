#ifndef NEBUTEST_MOCKPHYSICALDATACENTER_H_
#define NEBUTEST_MOCKPHYSICALDATACENTER_H_

#include "gmock/gmock.h"

#include "nebu/topology/physicalDataCenter.h"

using nebu::common::PhysicalDataCenter;
using nebu::common::PhysicalRoot;

namespace nebu
{
	namespace test
	{

		class MockPhysicalDataCenter : public PhysicalDataCenter
		{
		public:
			MockPhysicalDataCenter() : PhysicalDataCenter("") { };
//			virtual ~MockPhysicalDataCenter() { };

			MOCK_METHOD0(getUUID, std::string());
			MOCK_CONST_METHOD0(getParent, PhysicalRoot *());
			MOCK_METHOD1(setParent, void(PhysicalRoot *parent));

		private:
		};

	}
}

#endif

