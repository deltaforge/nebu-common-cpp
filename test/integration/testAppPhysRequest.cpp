
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "nebu/appPhysRequest.h"
#include "nebu/topology/physicalDataCenter.h"
#include "nebu/topology/physicalHost.h"
#include "nebu/topology/physicalLocalStore.h"
#include "nebu/topology/physicalNetworkStore.h"
#include "nebu/topology/physicalRack.h"
#include "nebu/topology/physicalRoot.h"

#include "mocks/mockNebuClient.h"

#include <fstream>
#include <sstream>

// Using declarations - standard library
using std::ifstream;
using std::make_shared;
using std::set;
using std::shared_ptr;
using std::string;
using std::stringstream;
using std::unordered_map;
using std::vector;
// Using declarations - nebu-common
using nebu::common::AppPhysRequest;
using nebu::common::NebuClient;
using nebu::common::PhysicalDataCenter;
using nebu::common::PhysicalHost;
using nebu::common::PhysicalLocalStore;
using nebu::common::PhysicalNetworkStore;
using nebu::common::PhysicalRack;
using nebu::common::PhysicalRoot;
using nebu::common::Traits;
// Using declarations - nebu-test
using nebu::test::MockNebuClient;

// Using declarations - gtest/gmock
using testing::ContainerEq;
using testing::Eq;
using testing::NotNull;
using testing::Return;
using testing::StrEq;

string readTestFile(const string &filename) {
	ifstream file(filename);
	stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

template<typename K, typename V>
vector<K> getKeySet(unordered_map<K, V> map) {
	vector<K> keySet;
	for (typename unordered_map<K, V>::iterator it = map.begin(); it != map.end(); it++) {
		keySet.push_back(it->first);
	}
	return keySet;
}

TEST(AppPhysRequestIntegrationTest, testGetPhysicalTopologyValidXML) {
	shared_ptr<MockNebuClient> mockNebuClient = make_shared<MockNebuClient>();
	AppPhysRequest request(mockNebuClient, "MyAppID");

	NebuClient::Response preparedResponse;
	preparedResponse.body = readTestFile("files/physicalTopology.xml");
	preparedResponse.status_code = 200;
	EXPECT_CALL(*mockNebuClient, performGET("/app/MyAppID/phys"))
		.WillRepeatedly(Return(preparedResponse));

	// Check root
	Traits<PhysicalRoot>::Ptr physicalRoot = request.getPhysicalTopology();
	EXPECT_THAT(physicalRoot, NotNull());
	EXPECT_THAT(physicalRoot->getUUID(), StrEq("root"));
	EXPECT_THAT(physicalRoot->getDataCenters().size(), Eq(1));

	// Check data center
	Traits<PhysicalDataCenter>::Ptr physicalDataCenter = physicalRoot->getDataCenters().begin()->second;
	EXPECT_THAT(physicalDataCenter, NotNull());
	EXPECT_THAT(physicalDataCenter->getUUID(), StrEq("dc"));
	EXPECT_THAT(physicalDataCenter->getRacks().size(), Eq(1));

	// Check rack
	Traits<PhysicalRack>::Ptr physicalRack = physicalDataCenter->getRacks().begin()->second;
	EXPECT_THAT(physicalRack, NotNull());
	EXPECT_THAT(physicalRack->getUUID(), StrEq("rack"));
	EXPECT_THAT(physicalRack->getHosts().size(), Eq(3));
	EXPECT_THAT(physicalRack->getNetworkStores().size(), Eq(2));

	// Check network stores
	Traits<PhysicalNetworkStore>::Map networkStores = physicalRack->getNetworkStores();
	vector<string> networkStoreIDs = getKeySet(networkStores);
	EXPECT_THAT(networkStores[networkStoreIDs[0]], NotNull());
	EXPECT_THAT(networkStores[networkStoreIDs[1]], NotNull());
	set<string> setNetworkStoreIDs(networkStoreIDs.begin(), networkStoreIDs.end());
	set<string> expectedNetworkStoreIDs({ string("x"), string("y") });
	EXPECT_THAT(setNetworkStoreIDs, ContainerEq(expectedNetworkStoreIDs));

	// Check hosts
	Traits<PhysicalHost>::Map hosts = physicalRack->getHosts();
	vector<string> hostIDs = getKeySet(hosts);
	EXPECT_THAT(hosts[hostIDs[0]], NotNull());
	EXPECT_THAT(hosts[hostIDs[1]], NotNull());
	EXPECT_THAT(hosts[hostIDs[2]], NotNull());
	set<string> setHostIDs(hostIDs.begin(), hostIDs.end());
	set<string> expectedHostIDs({ string("1"), string("2"), string("3") });
	EXPECT_THAT(setHostIDs, ContainerEq(expectedHostIDs));

	// Find host with id 2
	Traits<PhysicalHost>::Ptr physicalHostId2;
	if (hosts[hostIDs[0]]->getUUID() == "2") {
		physicalHostId2 = hosts[hostIDs[0]];
	} else if (hosts[hostIDs[1]]->getUUID() == "2") {
		physicalHostId2 = hosts[hostIDs[1]];
	} else {
		physicalHostId2 = hosts[hostIDs[2]];
	}

	// Check local store
	EXPECT_THAT(physicalHostId2->getLocalStores().size(), Eq(1));
	Traits<PhysicalLocalStore>::Ptr physicalLocalStore = physicalHostId2->getLocalStores().begin()->second;
	EXPECT_THAT(physicalLocalStore, NotNull());
	EXPECT_THAT(physicalLocalStore->getUUID(), StrEq("local")); 
}

int main(int argc, char **argv) {
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
