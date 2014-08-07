#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "nebu/topology/physicalNetworkStore.h"
#include "nebu/topology/physicalRack.h"

// Using declarations - nebu-common
using nebu::common::PhysicalNetworkStore;
using nebu::common::PhysicalRack;
using nebu::common::Traits;

// Using declarations - gtest/gmock
using testing::Contains;
using testing::Eq;
using testing::Pair;
using testing::StrEq;

TEST(PhysicalNetworkStoreTest, testConstructor) {
	PhysicalNetworkStore store("NetworkStoreA");
	EXPECT_THAT(store.getUUID(), StrEq("NetworkStoreA"));
}

TEST(PhysicalNetworkStoreTest, testCopyConstructor) {
	PhysicalNetworkStore store("NetworkStoreA");
	PhysicalNetworkStore copy(store);
	
	EXPECT_THAT(copy.getUUID(), StrEq("NetworkStoreA"));
}

TEST(PhysicalNetworkStoreTest, testGetSetParent) {
	PhysicalNetworkStore store("NetworkStoreA");
	Traits<PhysicalRack>::Ptr parent = Traits<PhysicalRack>::MakePtr("RackID");
	store.setParent(parent.get());
	EXPECT_THAT(store.getParent(), Eq(parent.get()));
}

int main(int argc, char **argv) {
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
