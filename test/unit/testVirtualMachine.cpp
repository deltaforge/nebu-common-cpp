
#include <gtest/gtest.h>

#include "nebu/virtualMachine.h"

// Using declarations - standard library
using std::string;
// Using declarations - nebu-common
using nebu::common::VirtualMachine;
using nebu::common::VMStatus;

TEST(VirtualMachineTest, testConstructor) {
	VirtualMachine vm("id");
	EXPECT_EQ("id", vm.getUUID());
}

TEST(VirtualMachineTest, testSetHostname) {
	VirtualMachine vm("id");
	string hostname("myhost-001");
	vm.setHostname(hostname);
	EXPECT_EQ(hostname, vm.getHostname());
}

TEST(VirtualMachineTest, testSetStatus) {
	VirtualMachine vm("id");
	vm.setStatus(VMStatus::ON);
	EXPECT_EQ(VMStatus::ON, vm.getStatus());
}

TEST(VirtualMachineTest, testSetPhysHost) {
	VirtualMachine vm("id");
	string physhost("physhost-1");
	vm.setPhysicalHostID(physhost);
	EXPECT_EQ(physhost, vm.getPhysicalHostID());
}

TEST(VirtualMachineTest, testSetPhysDisk) {
	VirtualMachine vm("id");
	string physdisk("physdisk-1");
	vm.setPhysicalStoreID(physdisk);
	EXPECT_EQ(physdisk, vm.getPhysicalStoreID());
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
