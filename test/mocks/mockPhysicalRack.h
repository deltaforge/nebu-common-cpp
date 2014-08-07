#ifndef NEBUTEST_MOCKPHYSICALRACK_H_
#define NEBUTEST_MOCKPHYSICALRACK_H_

#include "gmock/gmock.h"

#include "nebu/topology/physicalRack.h"

using nebu::common::PhysicalRack;
using nebu::common::PhysicalDataCenter;

namespace nebu
{
	namespace test
	{

		class MockPhysicalRack : public PhysicalRack
		{
		public:
			MockPhysicalRack() : PhysicalRack("") { };
//			virtual ~MockPhysicalRack() { };

			MOCK_METHOD0(getUUID, std::string());
			MOCK_CONST_METHOD0(getParent, PhysicalDataCenter *());
			MOCK_METHOD1(setParent, void(PhysicalDataCenter *parent));

		private:
		};

	}
}

#endif

