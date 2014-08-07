#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "nebu/topology/physicalLocalStore.h"
#include "nebu/topology/physicalHost.h"

// Using declarations - nebu-common
using nebu::common::PhysicalLocalStore;
using nebu::common::PhysicalHost;
using nebu::common::Traits;

// Using declarations - gtest/gmock
using testing::Contains;
using testing::Eq;
using testing::Pair;
using testing::StrEq;

TEST(PhysicalLocalStoreTest, testConstructor) {
	PhysicalLocalStore store("LocalStoreA");
	EXPECT_THAT(store.getUUID(), StrEq("LocalStoreA"));
}

TEST(PhysicalLocalStoreTest, testCopyConstructor) {
	PhysicalLocalStore store("LocalStoreA");
	PhysicalLocalStore copy(store);
	
	EXPECT_THAT(copy.getUUID(), StrEq("LocalStoreA"));
}

TEST(PhysicalLocalStoreTest, testGetSetParent) {
	PhysicalLocalStore store("LocalStoreA");
	Traits<PhysicalHost>::Ptr parent = Traits<PhysicalHost>::MakePtr("HostID");
	store.setParent(parent.get());
	EXPECT_THAT(store.getParent(), Eq(parent.get()));
}

int main(int argc, char **argv) {
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
