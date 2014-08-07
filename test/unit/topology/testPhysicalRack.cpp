#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "nebu/topology/physicalNetworkStore.h"
#include "nebu/topology/physicalRack.h"
#include "nebu/topology/physicalDataCenter.h"
#include "nebu/topology/physicalHost.h"

// Using declarations - nebu-common
using nebu::common::PhysicalRack;
using nebu::common::PhysicalNetworkStore;
using nebu::common::PhysicalDataCenter;
using nebu::common::PhysicalHost;
using nebu::common::Traits;

// Using declarations - gtest/gmock
using testing::Contains;
using testing::Eq;
using testing::Pair;
using testing::StrEq;
using testing::Not;

TEST(PhysicalRackTest, testConstructor) {
	PhysicalRack rack("RackA");
	EXPECT_THAT(rack.getUUID(), StrEq("RackA"));
}

TEST(PhysicalRackTest, testCopyConstructor) {
	PhysicalRack rack("RackA");
	PhysicalRack copy(rack);
	
	EXPECT_THAT(copy.getUUID(), StrEq("RackA"));
}

TEST(PhysicalRackTest, testGetSetParent) {
	PhysicalRack rack("RackA");
	Traits<PhysicalDataCenter>::Ptr parent = Traits<PhysicalDataCenter>::MakePtr("DataCenterID");
	rack.setParent(parent.get());
	EXPECT_THAT(rack.getParent(), Eq(parent.get()));
}

TEST(PhysicalRackTest, testGetSetDisksEmpty) {
	PhysicalRack rack("RackA");
	rack.setNetworkStores(Traits<PhysicalNetworkStore>::Map());
	EXPECT_THAT(rack.getNetworkStores().size(), Eq(0));
}

TEST(PhysicalRackTest, testGetSetDisksFilled) {
	PhysicalRack rack("RackA");
	Traits<PhysicalNetworkStore>::Map stores;
	stores["StoreA"] = Traits<PhysicalNetworkStore>::MakePtr("StoreA");
	stores["StoreB"] = Traits<PhysicalNetworkStore>::MakePtr("StoreB");
	stores["StoreC"] = Traits<PhysicalNetworkStore>::MakePtr("StoreC");
	rack.setNetworkStores(stores);

	EXPECT_THAT(rack.getNetworkStores().size(), Eq(3));
	EXPECT_THAT(rack.getNetworkStores(), Contains(Pair("StoreA", stores["StoreA"])));
	EXPECT_THAT(rack.getNetworkStores(), Contains(Pair("StoreB", stores["StoreB"])));
	EXPECT_THAT(rack.getNetworkStores(), Contains(Pair("StoreC", stores["StoreC"])));
}

TEST(PhysicalRackTest, testAddDisk) {
	PhysicalRack rack("RackA");
	Traits<PhysicalNetworkStore>::Ptr store = Traits<PhysicalNetworkStore>::MakePtr("StoreA");
	rack.addNetworkStore(store);
	EXPECT_THAT(rack.getNetworkStores().size(), Eq(1));
	EXPECT_THAT(rack.getNetworkStores(), Contains(Pair("StoreA", store)));
}

TEST(PhysicalRackTest, testAddNullDisk) {
	PhysicalRack rack("RackA");
	rack.addNetworkStore(Traits<PhysicalNetworkStore>::Ptr());
	EXPECT_THAT(rack.getNetworkStores().size(), Eq(0));
}

TEST(PhysicalRackTest, testAddDifferentDisks) {
	PhysicalRack rack("RackA");
	Traits<PhysicalNetworkStore>::Ptr store = Traits<PhysicalNetworkStore>::MakePtr("StoreA");
	Traits<PhysicalNetworkStore>::Ptr store2 = Traits<PhysicalNetworkStore>::MakePtr("StoreB");
	rack.addNetworkStore(store);
	rack.addNetworkStore(store2);
	EXPECT_THAT(rack.getNetworkStores().size(), Eq(2));
	EXPECT_THAT(rack.getNetworkStores(), Contains(Pair("StoreA", store)));
	EXPECT_THAT(rack.getNetworkStores(), Contains(Pair("StoreB", store2)));
}

TEST(PhysicalRackTest, testAddSameDisks) {
	PhysicalRack rack("RackA");
	Traits<PhysicalNetworkStore>::Ptr store = Traits<PhysicalNetworkStore>::MakePtr("StoreA");
	Traits<PhysicalNetworkStore>::Ptr store2 = Traits<PhysicalNetworkStore>::MakePtr("StoreA");
	rack.addNetworkStore(store);
	rack.addNetworkStore(store2);
	EXPECT_THAT(rack.getNetworkStores().size(), Eq(1));
	EXPECT_THAT(rack.getNetworkStores(), Contains(Pair("StoreA", store2)));
}

TEST(PhysicalRackTest, testRemoveDisk) {
	PhysicalRack rack("RackA");
	Traits<PhysicalNetworkStore>::Ptr store = Traits<PhysicalNetworkStore>::MakePtr("StoreA");
	rack.addNetworkStore(store);
	rack.removeNetworkStore("StoreA");
	EXPECT_THAT(rack.getNetworkStores(), Not(Contains(Pair("StoreA", store))));
}

TEST(PhysicalRackTest, testRemoveNonExistingDisk) {
	PhysicalRack rack("RackA");
	Traits<PhysicalNetworkStore>::Ptr store = Traits<PhysicalNetworkStore>::MakePtr("StoreA");
	rack.addNetworkStore(store);
	rack.removeNetworkStore("StoreB");
	EXPECT_THAT(rack.getNetworkStores(), Contains(Pair("StoreA", store)));
}

TEST(PhysicalRackTest, testGetSetHostsEmpty) {
	PhysicalRack rack("RackA");
	rack.setHosts(Traits<PhysicalHost>::Map());
	EXPECT_THAT(rack.getHosts().size(), Eq(0));
}

TEST(PhysicalRackTest, testGetSetHostsFilled) {
	PhysicalRack rack("RackA");
	Traits<PhysicalHost>::Map stores;
	stores["StoreA"] = Traits<PhysicalHost>::MakePtr("StoreA");
	stores["StoreB"] = Traits<PhysicalHost>::MakePtr("StoreB");
	stores["StoreC"] = Traits<PhysicalHost>::MakePtr("StoreC");
	rack.setHosts(stores);

	EXPECT_THAT(rack.getHosts().size(), Eq(3));
	EXPECT_THAT(rack.getHosts(), Contains(Pair("StoreA", stores["StoreA"])));
	EXPECT_THAT(rack.getHosts(), Contains(Pair("StoreB", stores["StoreB"])));
	EXPECT_THAT(rack.getHosts(), Contains(Pair("StoreC", stores["StoreC"])));
}

TEST(PhysicalRackTest, testAddHost) {
	PhysicalRack rack("RackA");
	Traits<PhysicalHost>::Ptr store = Traits<PhysicalHost>::MakePtr("StoreA");
	rack.addHost(store);
	EXPECT_THAT(rack.getHosts().size(), Eq(1));
	EXPECT_THAT(rack.getHosts(), Contains(Pair("StoreA", store)));
}

TEST(PhysicalRackTest, testAddNullHost) {
	PhysicalRack rack("RackA");
	rack.addHost(Traits<PhysicalHost>::Ptr());
	EXPECT_THAT(rack.getHosts().size(), Eq(0));
}

TEST(PhysicalRackTest, testAddDifferentHosts) {
	PhysicalRack rack("RackA");
	Traits<PhysicalHost>::Ptr store = Traits<PhysicalHost>::MakePtr("StoreA");
	Traits<PhysicalHost>::Ptr store2 = Traits<PhysicalHost>::MakePtr("StoreB");
	rack.addHost(store);
	rack.addHost(store2);
	EXPECT_THAT(rack.getHosts().size(), Eq(2));
	EXPECT_THAT(rack.getHosts(), Contains(Pair("StoreA", store)));
	EXPECT_THAT(rack.getHosts(), Contains(Pair("StoreB", store2)));
}

TEST(PhysicalRackTest, testAddSameHosts) {
	PhysicalRack rack("RackA");
	Traits<PhysicalHost>::Ptr store = Traits<PhysicalHost>::MakePtr("StoreA");
	Traits<PhysicalHost>::Ptr store2 = Traits<PhysicalHost>::MakePtr("StoreA");
	rack.addHost(store);
	rack.addHost(store2);
	EXPECT_THAT(rack.getHosts().size(), Eq(1));
	EXPECT_THAT(rack.getHosts(), Contains(Pair("StoreA", store2)));
}

TEST(PhysicalRackTest, testRemoveHost) {
	PhysicalRack rack("RackA");
	Traits<PhysicalHost>::Ptr store = Traits<PhysicalHost>::MakePtr("StoreA");
	rack.addHost(store);
	rack.removeHost("StoreA");
	EXPECT_THAT(rack.getHosts(), Not(Contains(Pair("StoreA", store))));
}

TEST(PhysicalRackTest, testRemoveNonExistingHost) {
	PhysicalRack rack("RackA");
	Traits<PhysicalHost>::Ptr store = Traits<PhysicalHost>::MakePtr("StoreA");
	rack.addHost(store);
	rack.removeHost("StoreB");
	EXPECT_THAT(rack.getHosts(), Contains(Pair("StoreA", store)));
}
int main(int argc, char **argv) {
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
