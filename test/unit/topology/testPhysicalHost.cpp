#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "nebu/topology/physicalLocalStore.h"
#include "nebu/topology/physicalHost.h"
#include "nebu/topology/physicalRack.h"

// Using declarations - nebu-common
using nebu::common::PhysicalHost;
using nebu::common::PhysicalLocalStore;
using nebu::common::PhysicalRack;
using nebu::common::Traits;

// Using declarations - gtest/gmock
using testing::Contains;
using testing::Eq;
using testing::Pair;
using testing::StrEq;
using testing::Not;

TEST(PhysicalHostTest, testConstructor) {
	PhysicalHost host("HostA");
	EXPECT_THAT(host.getUUID(), StrEq("HostA"));
}

TEST(PhysicalHostTest, testCopyConstructor) {
	PhysicalHost host("HostA");
	PhysicalHost copy(host);
	
	EXPECT_THAT(copy.getUUID(), StrEq("HostA"));
}

TEST(PhysicalHostTest, testGetSetParent) {
	PhysicalHost host("HostA");
	Traits<PhysicalRack>::Ptr parent = Traits<PhysicalRack>::MakePtr("RackID");
	host.setParent(parent.get());
	EXPECT_THAT(host.getParent(), Eq(parent.get()));
}

TEST(PhysicalHostTest, testGetSetDisksEmpty) {
	PhysicalHost host("HostA");
	host.setLocalStores(Traits<PhysicalLocalStore>::Map());
	EXPECT_THAT(host.getLocalStores().size(), Eq(0));
}

TEST(PhysicalHostTest, testGetSetDisksFilled) {
	PhysicalHost host("HostA");
	Traits<PhysicalLocalStore>::Map stores;
	stores["StoreA"] = Traits<PhysicalLocalStore>::MakePtr("StoreA");
	stores["StoreB"] = Traits<PhysicalLocalStore>::MakePtr("StoreB");
	stores["StoreC"] = Traits<PhysicalLocalStore>::MakePtr("StoreC");
	host.setLocalStores(stores);

	EXPECT_THAT(host.getLocalStores().size(), Eq(3));
	EXPECT_THAT(host.getLocalStores(), Contains(Pair("StoreA", stores["StoreA"])));
	EXPECT_THAT(host.getLocalStores(), Contains(Pair("StoreB", stores["StoreB"])));
	EXPECT_THAT(host.getLocalStores(), Contains(Pair("StoreC", stores["StoreC"])));
}

TEST(PhysicalHostTest, testAddDisk) {
	PhysicalHost host("HostA");
	Traits<PhysicalLocalStore>::Ptr store = Traits<PhysicalLocalStore>::MakePtr("StoreA");
	host.addLocalStore(store);
	EXPECT_THAT(host.getLocalStores().size(), Eq(1));
	EXPECT_THAT(host.getLocalStores(), Contains(Pair("StoreA", store)));
}

TEST(PhysicalHostTest, testAddNullDisk) {
	PhysicalHost host("HostA");
	host.addLocalStore(Traits<PhysicalLocalStore>::Ptr());
	EXPECT_THAT(host.getLocalStores().size(), Eq(0));
}

TEST(PhysicalHostTest, testAddDifferentDisks) {
	PhysicalHost host("HostA");
	Traits<PhysicalLocalStore>::Ptr store = Traits<PhysicalLocalStore>::MakePtr("StoreA");
	Traits<PhysicalLocalStore>::Ptr store2 = Traits<PhysicalLocalStore>::MakePtr("StoreB");
	host.addLocalStore(store);
	host.addLocalStore(store2);
	EXPECT_THAT(host.getLocalStores().size(), Eq(2));
	EXPECT_THAT(host.getLocalStores(), Contains(Pair("StoreA", store)));
	EXPECT_THAT(host.getLocalStores(), Contains(Pair("StoreB", store2)));
}

TEST(PhysicalHostTest, testAddSameDisks) {
	PhysicalHost host("HostA");
	Traits<PhysicalLocalStore>::Ptr store = Traits<PhysicalLocalStore>::MakePtr("StoreA");
	Traits<PhysicalLocalStore>::Ptr store2 = Traits<PhysicalLocalStore>::MakePtr("StoreA");
	host.addLocalStore(store);
	host.addLocalStore(store2);
	EXPECT_THAT(host.getLocalStores().size(), Eq(1));
	EXPECT_THAT(host.getLocalStores(), Contains(Pair("StoreA", store2)));
}

TEST(PhysicalHostTest, testRemoveDisk) {
	PhysicalHost host("HostA");
	Traits<PhysicalLocalStore>::Ptr store = Traits<PhysicalLocalStore>::MakePtr("StoreA");
	host.addLocalStore(store);
	host.removeLocalStore("StoreA");
	EXPECT_THAT(host.getLocalStores(), Not(Contains(Pair("StoreA", store))));
}

TEST(PhysicalHostTest, testRemoveNonExistingDisk) {
	PhysicalHost host("HostA");
	Traits<PhysicalLocalStore>::Ptr store = Traits<PhysicalLocalStore>::MakePtr("StoreA");
	host.addLocalStore(store);
	host.removeLocalStore("StoreB");
	EXPECT_THAT(host.getLocalStores(), Contains(Pair("StoreA", store)));
}
int main(int argc, char **argv) {
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
