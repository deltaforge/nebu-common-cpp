#ifndef NEBUTEST_MOCKPHYSICALLOCALSTORE_H_
#define NEBUTEST_MOCKPHYSICALLOCALSTORE_H_

#include "gmock/gmock.h"

#include "nebu/topology/physicalLocalStore.h"

using nebu::common::PhysicalLocalStore;
using nebu::common::PhysicalHost;

namespace nebu
{
	namespace test
	{

		class MockPhysicalLocalStore : public PhysicalLocalStore
		{
		public:
			MockPhysicalLocalStore() : PhysicalLocalStore("") { };
//			virtual ~MockPhysicalLocalStore() { };

			MOCK_METHOD0(getUUID, std::string());
			MOCK_CONST_METHOD0(getParent, PhysicalHost *());
			MOCK_METHOD1(setParent, void(PhysicalHost *parent));

		private:
		};

	}
}

#endif

