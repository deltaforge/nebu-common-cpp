
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "nebu/topology/physicalDataCenter.h"
#include "nebu/topology/physicalHost.h"
#include "nebu/topology/physicalLocalStore.h"
#include "nebu/topology/physicalNetworkStore.h"
#include "nebu/topology/physicalRack.h"
#include "nebu/topology/physicalRoot.h"

// Using declarations - nebu-common
using nebu::common::PhysicalDataCenter;
using nebu::common::PhysicalRack;
using nebu::common::PhysicalRoot;
using nebu::common::Traits;

// Using declarations - gtest/gmock
using testing::Contains;
using testing::Eq;
using testing::Pair;
using testing::StrEq;

TEST(PhysicalDataCenterTest, testConstructor) {
	PhysicalDataCenter dc("DataCenterA");
	EXPECT_THAT(dc.getUUID(), StrEq("DataCenterA"));
}

TEST(PhysicalDataCenterTest, testGetSetParent) {
	PhysicalDataCenter dc("DataCenterA");
	Traits<PhysicalRoot>::Ptr root = Traits<PhysicalRoot>::MakePtr("RootID");
	dc.setParent(root.get());
	EXPECT_THAT(dc.getParent(), Eq(root.get()));
}

TEST(PhysicalDataCenterTest, testGetSetRacksEmpty) {
	PhysicalDataCenter dc("DataCenterA");
	dc.setRacks(Traits<PhysicalRack>::Map());
	EXPECT_THAT(dc.getRacks().size(), Eq(0));
}

TEST(PhysicalDataCenterTest, testGetSetRacksFilled) {
	PhysicalDataCenter dc("DataCenterA");
	Traits<PhysicalRack>::Map racks;
	racks["RackA"] = Traits<PhysicalRack>::MakePtr("RackA");
	racks["RackB"] = Traits<PhysicalRack>::MakePtr("RackB");
	racks["RackC"] = Traits<PhysicalRack>::MakePtr("RackC");
	dc.setRacks(racks);

	EXPECT_THAT(dc.getRacks().size(), Eq(3));
	EXPECT_THAT(dc.getRacks(), Contains(Pair("RackA", racks["RackA"])));
	EXPECT_THAT(dc.getRacks(), Contains(Pair("RackB", racks["RackB"])));
	EXPECT_THAT(dc.getRacks(), Contains(Pair("RackC", racks["RackC"])));
}

TEST(PhysicalDataCenterTest, testAddRackToEmpty) {
	PhysicalDataCenter dc("DataCenterA");
	Traits<PhysicalRack>::Ptr rack = Traits<PhysicalRack>::MakePtr("RackA");
	dc.addRack(rack);

	EXPECT_THAT(dc.getRacks().size(), Eq(1));
	EXPECT_THAT(dc.getRacks(), Contains(Pair("RackA", rack)));
}

TEST(PhysicalDataCenterTest, testRemoveRack) {
	PhysicalDataCenter dc("DataCenterA");
	Traits<PhysicalRack>::Ptr rack = Traits<PhysicalRack>::MakePtr("RackA");
	dc.addRack(rack);
	dc.removeRack(rack->getUUID());

	EXPECT_THAT(dc.getRacks().size(), Eq(0));
}

int main(int argc, char **argv) {
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
