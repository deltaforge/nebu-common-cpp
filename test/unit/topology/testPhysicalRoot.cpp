#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "nebu/topology/physicalDataCenter.h"
#include "nebu/topology/physicalRoot.h"
#include "nebu/topology/physicalRack.h"

// Using declarations - nebu-common
using nebu::common::PhysicalRoot;
using nebu::common::PhysicalDataCenter;
using nebu::common::PhysicalRack;
using nebu::common::Traits;

// Using declarations - gtest/gmock
using testing::Contains;
using testing::Eq;
using testing::Pair;
using testing::StrEq;
using testing::Not;

TEST(PhysicalRootTest, testConstructor) {
	PhysicalRoot root("RootA");
	EXPECT_THAT(root.getUUID(), StrEq("RootA"));
}

TEST(PhysicalRootTest, testCopyConstructor) {
	PhysicalRoot root("RootA");
	PhysicalRoot copy(root);
	
	EXPECT_THAT(copy.getUUID(), StrEq("RootA"));
}

TEST(PhysicalRootTest, testGetSetDataCentersEmpty) {
	PhysicalRoot root("RootA");
	root.setDataCenters(Traits<PhysicalDataCenter>::Map());
	EXPECT_THAT(root.getDataCenters().size(), Eq(0));
}

TEST(PhysicalRootTest, testGetSetDataCentersFilled) {
	PhysicalRoot root("RootA");
	Traits<PhysicalDataCenter>::Map stores;
	stores["StoreA"] = Traits<PhysicalDataCenter>::MakePtr("StoreA");
	stores["StoreB"] = Traits<PhysicalDataCenter>::MakePtr("StoreB");
	stores["StoreC"] = Traits<PhysicalDataCenter>::MakePtr("StoreC");
	root.setDataCenters(stores);

	EXPECT_THAT(root.getDataCenters().size(), Eq(3));
	EXPECT_THAT(root.getDataCenters(), Contains(Pair("StoreA", stores["StoreA"])));
	EXPECT_THAT(root.getDataCenters(), Contains(Pair("StoreB", stores["StoreB"])));
	EXPECT_THAT(root.getDataCenters(), Contains(Pair("StoreC", stores["StoreC"])));
}

TEST(PhysicalRootTest, testAddDataCenter) {
	PhysicalRoot root("RootA");
	Traits<PhysicalDataCenter>::Ptr store = Traits<PhysicalDataCenter>::MakePtr("StoreA");
	root.addDataCenter(store);
	EXPECT_THAT(root.getDataCenters().size(), Eq(1));
	EXPECT_THAT(root.getDataCenters(), Contains(Pair("StoreA", store)));
}

TEST(PhysicalRootTest, testAddNullDataCenter) {
	PhysicalRoot root("RootA");
	root.addDataCenter(Traits<PhysicalDataCenter>::Ptr());
	EXPECT_THAT(root.getDataCenters().size(), Eq(0));
}

TEST(PhysicalRootTest, testAddDifferentDataCenters) {
	PhysicalRoot root("RootA");
	Traits<PhysicalDataCenter>::Ptr store = Traits<PhysicalDataCenter>::MakePtr("StoreA");
	Traits<PhysicalDataCenter>::Ptr store2 = Traits<PhysicalDataCenter>::MakePtr("StoreB");
	root.addDataCenter(store);
	root.addDataCenter(store2);
	EXPECT_THAT(root.getDataCenters().size(), Eq(2));
	EXPECT_THAT(root.getDataCenters(), Contains(Pair("StoreA", store)));
	EXPECT_THAT(root.getDataCenters(), Contains(Pair("StoreB", store2)));
}

TEST(PhysicalRootTest, testAddSameDataCenters) {
	PhysicalRoot root("RootA");
	Traits<PhysicalDataCenter>::Ptr store = Traits<PhysicalDataCenter>::MakePtr("StoreA");
	Traits<PhysicalDataCenter>::Ptr store2 = Traits<PhysicalDataCenter>::MakePtr("StoreA");
	root.addDataCenter(store);
	root.addDataCenter(store2);
	EXPECT_THAT(root.getDataCenters().size(), Eq(1));
	EXPECT_THAT(root.getDataCenters(), Contains(Pair("StoreA", store2)));
}

TEST(PhysicalRootTest, testRemoveDataCenter) {
	PhysicalRoot root("RootA");
	Traits<PhysicalDataCenter>::Ptr store = Traits<PhysicalDataCenter>::MakePtr("StoreA");
	root.addDataCenter(store);
	root.removeDataCenter("StoreA");
	EXPECT_THAT(root.getDataCenters(), Not(Contains(Pair("StoreA", store))));
}

TEST(PhysicalRootTest, testRemoveNonExistingDataCenter) {
	PhysicalRoot root("RootA");
	Traits<PhysicalDataCenter>::Ptr store = Traits<PhysicalDataCenter>::MakePtr("StoreA");
	root.addDataCenter(store);
	root.removeDataCenter("StoreB");
	EXPECT_THAT(root.getDataCenters(), Contains(Pair("StoreA", store)));
}
int main(int argc, char **argv) {
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
