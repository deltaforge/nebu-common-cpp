#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "tinyxml2.h"

#include "nebu/topology/physicalRackFactory.h"
#include "mocks/mockPhysicalNetworkStoreFactory.h"
#include "mocks/mockPhysicalNetworkStore.h"
#include "mocks/mockPhysicalHostFactory.h"
#include "mocks/mockPhysicalHost.h"
#include "nebu/util/exceptions.h"
#include "nebu/util/xmlUtil.h"

// Using declarations - tinyxml2
using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;
using std::string;
using std::shared_ptr;
// Using declarations - nebu-common
using nebu::common::PhysicalRack;
using nebu::common::PhysicalRackFactory;
using nebu::common::PhysicalNetworkStoreFactory;
using nebu::common::PhysicalHostFactory;
using nebu::common::XMLParseException;
using nebu::common::XMLUtil;
using nebu::common::Traits;
using nebu::test::MockPhysicalNetworkStore;
using nebu::test::MockPhysicalNetworkStoreFactory;
using nebu::test::MockPhysicalHost;
using nebu::test::MockPhysicalHostFactory;

// Using declarations - gtest/gmock
using ::testing::Eq;
using ::testing::NotNull;
using ::testing::Contains;
using ::testing::Return;
using ::testing::_;

TEST(PhysicalRackFactoryTest, testGetInstance) {
		shared_ptr<PhysicalRackFactory> factory = PhysicalRackFactory::getInstance();
		EXPECT_THAT(factory.get(), NotNull());
}

TEST(PhysicalRackFactoryTest, testParseXMLNull) {
	PhysicalRackFactory factory;

	try {
		factory.parseXML(NULL);
		FAIL() << "Expected XMLParseException";
	} catch(XMLParseException &ex) {
		SUCCEED();
	}
}

TEST(PhysicalRackFactoryTest, testParseXMLEmptyXML) {
	PhysicalRackFactory factory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement("");

	try {
		factory.parseXML(elem);
		FAIL() << "Expected XMLParseException";
	} catch(XMLParseException &ex) {
		SUCCEED();
	}
}

TEST(PhysicalRackFactoryTest, testParseXMLWrongRoot) {
	PhysicalRackFactory factory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement("thisisnotthecorrectrootname");

	try {
		factory.parseXML(elem);
		FAIL() << "Expected XMLParseException";
	} catch(XMLParseException &ex) {
		SUCCEED();
	}
}

TEST(PhysicalRackFactoryTest, testParseXMLNoIDAttribute) {
	PhysicalRackFactory factory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement(PhysicalRackFactory::ROOT_NAME.c_str());

	try {
		factory.parseXML(elem);
		FAIL() << "Expected XMLParseException";
	} catch(XMLParseException &ex) {
		SUCCEED();
	}
}

TEST(PhysicalRackFactoryTest, testParseXMLCheckID) {
	PhysicalRackFactory factory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement(PhysicalRackFactory::ROOT_NAME.c_str());
	elem->SetAttribute(PhysicalRackFactory::ATTR_ID.c_str(), "id");

	Traits<PhysicalRack>::Ptr object = factory.parseXML(elem);

	EXPECT_THAT(object->getUUID(), Eq("id"));
}

TEST(PhysicalRackFactoryTest, testParseXMLCheckNoDisks) {
	PhysicalRackFactory factory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement(PhysicalRackFactory::ROOT_NAME.c_str());
	elem->SetAttribute(PhysicalRackFactory::ATTR_ID.c_str(), "id");

	Traits<PhysicalRack>::Ptr object = factory.parseXML(elem);

	EXPECT_THAT(object->getNetworkStores().size(), Eq(0));
}

TEST(PhysicalRackFactoryTest, testParseXMLCheckSingleDisk) {
	PhysicalRackFactory factory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement(PhysicalRackFactory::ROOT_NAME.c_str());
	elem->SetAttribute(PhysicalRackFactory::ATTR_ID.c_str(), "id");
	XMLElement *disk = doc.NewElement(PhysicalNetworkStoreFactory::ROOT_NAME.c_str());
	elem->InsertEndChild(disk);

	Traits<MockPhysicalNetworkStoreFactory>::Ptr mock = Traits<MockPhysicalNetworkStoreFactory>::MakePtr();
	Traits<MockPhysicalNetworkStore>::Ptr mockedDisk = Traits<MockPhysicalNetworkStore>::MakePtr();
	PhysicalNetworkStoreFactory::setInstance(mock);
	EXPECT_CALL(*mock, parseXML(disk)).WillOnce(Return(mockedDisk));
	EXPECT_CALL(*mockedDisk, setParent(_));
	EXPECT_CALL(*mockedDisk, getUUID()).WillOnce(Return("disk"));
	
	Traits<PhysicalRack>::Ptr object = factory.parseXML(elem);

	EXPECT_THAT(object->getNetworkStores().size(), Eq(1));
	PhysicalNetworkStoreFactory::setInstance(Traits<MockPhysicalNetworkStoreFactory>::Ptr());
}

TEST(PhysicalRackFactoryTest, testParseXMLCheckTripleDisks) {
	PhysicalRackFactory factory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement(PhysicalRackFactory::ROOT_NAME.c_str());
	elem->SetAttribute(PhysicalRackFactory::ATTR_ID.c_str(), "id");
	XMLElement *disk = doc.NewElement(PhysicalNetworkStoreFactory::ROOT_NAME.c_str());
	elem->InsertEndChild(disk);
	XMLElement *disk1 = doc.NewElement(PhysicalNetworkStoreFactory::ROOT_NAME.c_str());
	elem->InsertEndChild(disk1);
	XMLElement *disk2 = doc.NewElement(PhysicalNetworkStoreFactory::ROOT_NAME.c_str());
	elem->InsertEndChild(disk2);

	Traits<MockPhysicalNetworkStoreFactory>::Ptr mock = Traits<MockPhysicalNetworkStoreFactory>::MakePtr();
	Traits<MockPhysicalNetworkStore>::Ptr mockedDisk = Traits<MockPhysicalNetworkStore>::MakePtr();
	PhysicalNetworkStoreFactory::setInstance(mock);
	EXPECT_CALL(*mock, parseXML(_)).WillRepeatedly(Return(mockedDisk));
	EXPECT_CALL(*mockedDisk, setParent(_)).Times(3);
	EXPECT_CALL(*mockedDisk, getUUID()).WillOnce(Return("disk")).WillOnce(Return("disk1")).WillOnce(Return("disk2"));
	
	Traits<PhysicalRack>::Ptr object = factory.parseXML(elem);

	EXPECT_THAT(object->getNetworkStores().size(), Eq(3));
	PhysicalNetworkStoreFactory::setInstance(Traits<MockPhysicalNetworkStoreFactory>::Ptr());
}

TEST(PhysicalRackFactoryTest, testParseXMLCheckNoHosts) {
	PhysicalRackFactory factory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement(PhysicalRackFactory::ROOT_NAME.c_str());
	elem->SetAttribute(PhysicalRackFactory::ATTR_ID.c_str(), "id");

	Traits<PhysicalRack>::Ptr object = factory.parseXML(elem);

	EXPECT_THAT(object->getHosts().size(), Eq(0));
}

TEST(PhysicalRackFactoryTest, testParseXMLCheckSingleHost) {
	PhysicalRackFactory factory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement(PhysicalRackFactory::ROOT_NAME.c_str());
	elem->SetAttribute(PhysicalRackFactory::ATTR_ID.c_str(), "id");
	XMLElement *host = doc.NewElement(PhysicalHostFactory::ROOT_NAME.c_str());
	elem->InsertEndChild(host);

	Traits<MockPhysicalHostFactory>::Ptr mock = Traits<MockPhysicalHostFactory>::MakePtr();
	Traits<MockPhysicalHost>::Ptr mockedHost = Traits<MockPhysicalHost>::MakePtr();
	PhysicalHostFactory::setInstance(mock);
	EXPECT_CALL(*mock, parseXML(host)).WillOnce(Return(mockedHost));
	EXPECT_CALL(*mockedHost, setParent(_));
	EXPECT_CALL(*mockedHost, getUUID()).WillOnce(Return("host"));
	
	Traits<PhysicalRack>::Ptr object = factory.parseXML(elem);

	EXPECT_THAT(object->getHosts().size(), Eq(1));
	PhysicalHostFactory::setInstance(Traits<MockPhysicalHostFactory>::Ptr());
}

TEST(PhysicalRackFactoryTest, testParseXMLCheckTripleHosts) {
	PhysicalRackFactory factory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement(PhysicalRackFactory::ROOT_NAME.c_str());
	elem->SetAttribute(PhysicalRackFactory::ATTR_ID.c_str(), "id");
	XMLElement *host = doc.NewElement(PhysicalHostFactory::ROOT_NAME.c_str());
	elem->InsertEndChild(host);
	XMLElement *host1 = doc.NewElement(PhysicalHostFactory::ROOT_NAME.c_str());
	elem->InsertEndChild(host1);
	XMLElement *host2 = doc.NewElement(PhysicalHostFactory::ROOT_NAME.c_str());
	elem->InsertEndChild(host2);

	Traits<MockPhysicalHostFactory>::Ptr mock = Traits<MockPhysicalHostFactory>::MakePtr();
	Traits<MockPhysicalHost>::Ptr mockedHost = Traits<MockPhysicalHost>::MakePtr();
	PhysicalHostFactory::setInstance(mock);
	EXPECT_CALL(*mock, parseXML(_)).WillRepeatedly(Return(mockedHost));
	EXPECT_CALL(*mockedHost, setParent(_)).Times(3);
	EXPECT_CALL(*mockedHost, getUUID()).WillOnce(Return("host")).WillOnce(Return("host1")).WillOnce(Return("host2"));
	
	Traits<PhysicalRack>::Ptr object = factory.parseXML(elem);

	EXPECT_THAT(object->getHosts().size(), Eq(3));
	PhysicalHostFactory::setInstance(Traits<MockPhysicalHostFactory>::Ptr());
}

int main(int argc, char **argv) {
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
