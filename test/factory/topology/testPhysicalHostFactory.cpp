#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "tinyxml2.h"

#include "nebu/topology/physicalHostFactory.h"
#include "mocks/mockPhysicalLocalStoreFactory.h"
#include "mocks/mockPhysicalLocalStore.h"
#include "nebu/util/exceptions.h"
#include "nebu/util/xmlUtil.h"

// Using declarations - tinyxml2
using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;
using std::string;
using std::shared_ptr;
using std::static_pointer_cast;
using std::dynamic_pointer_cast;
// Using declarations - nebu-common
using nebu::common::PhysicalHost;
using nebu::common::PhysicalHostFactory;
using nebu::common::PhysicalLocalStoreFactory;
using nebu::common::XMLParseException;
using nebu::common::XMLUtil;
using nebu::common::Traits;
using nebu::test::MockPhysicalLocalStore;
using nebu::test::MockPhysicalLocalStoreFactory;

// Using declarations - gtest/gmock
using ::testing::Eq;
using ::testing::NotNull;
using ::testing::Contains;
using ::testing::Return;
using ::testing::_;

TEST(PhysicalHostFactoryTest, testGetInstance) {
		shared_ptr<PhysicalHostFactory> factory = PhysicalHostFactory::getInstance();
		EXPECT_THAT(factory.get(), NotNull());
}

TEST(PhysicalHostFactoryTest, testParseXMLNull) {
	PhysicalHostFactory factory;

	try {
		factory.parseXML(NULL);
		FAIL() << "Expected XMLParseException";
	} catch(XMLParseException &ex) {
		SUCCEED();
	}
}

TEST(PhysicalHostFactoryTest, testParseXMLEmptyXML) {
	PhysicalHostFactory factory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement("");

	try {
		factory.parseXML(elem);
		FAIL() << "Expected XMLParseException";
	} catch(XMLParseException &ex) {
		SUCCEED();
	}
}

TEST(PhysicalHostFactoryTest, testParseXMLWrongRoot) {
	PhysicalHostFactory factory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement("thisisnotthecorrectrootname");

	try {
		factory.parseXML(elem);
		FAIL() << "Expected XMLParseException";
	} catch(XMLParseException &ex) {
		SUCCEED();
	}
}

TEST(PhysicalHostFactoryTest, testParseXMLNoIDAttribute) {
	PhysicalHostFactory factory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement(PhysicalHostFactory::ROOT_NAME.c_str());

	try {
		factory.parseXML(elem);
		FAIL() << "Expected XMLParseException";
	} catch(XMLParseException &ex) {
		SUCCEED();
	}
}

TEST(PhysicalHostFactoryTest, testParseXMLCheckID) {
	PhysicalHostFactory factory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement(PhysicalHostFactory::ROOT_NAME.c_str());
	elem->SetAttribute(PhysicalHostFactory::ATTR_ID.c_str(), "id");

	Traits<PhysicalHost>::Ptr object = factory.parseXML(elem);

	EXPECT_THAT(object->getUUID(), Eq("id"));
}

TEST(PhysicalHostFactoryTest, testParseXMLCheckNoDisks) {
	PhysicalHostFactory factory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement(PhysicalHostFactory::ROOT_NAME.c_str());
	elem->SetAttribute(PhysicalHostFactory::ATTR_ID.c_str(), "id");

	Traits<PhysicalHost>::Ptr object = factory.parseXML(elem);

	EXPECT_THAT(object->getLocalStores().size(), Eq(0));
}

TEST(PhysicalHostFactoryTest, testParseXMLCheckSingleDisk) {
	PhysicalHostFactory factory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement(PhysicalHostFactory::ROOT_NAME.c_str());
	elem->SetAttribute(PhysicalHostFactory::ATTR_ID.c_str(), "id");
	XMLElement *disk = doc.NewElement(PhysicalLocalStoreFactory::ROOT_NAME.c_str());
	elem->InsertEndChild(disk);

	Traits<MockPhysicalLocalStoreFactory>::Ptr mock = Traits<MockPhysicalLocalStoreFactory>::MakePtr();
	Traits<MockPhysicalLocalStore>::Ptr mockedDisk = Traits<MockPhysicalLocalStore>::MakePtr();
	PhysicalLocalStoreFactory::setInstance(mock);
	EXPECT_CALL(*mock, parseXML(disk)).WillOnce(Return(mockedDisk));
	EXPECT_CALL(*mockedDisk, setParent(_));
	EXPECT_CALL(*mockedDisk, getUUID()).WillOnce(Return("disk"));
	
	Traits<PhysicalHost>::Ptr object = factory.parseXML(elem);

	EXPECT_THAT(object->getLocalStores().size(), Eq(1));
	PhysicalLocalStoreFactory::setInstance(Traits<MockPhysicalLocalStoreFactory>::Ptr());
}

TEST(PhysicalHostFactoryTest, testParseXMLCheckTripleDisks) {
	PhysicalHostFactory factory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement(PhysicalHostFactory::ROOT_NAME.c_str());
	elem->SetAttribute(PhysicalHostFactory::ATTR_ID.c_str(), "id");
	XMLElement *disk = doc.NewElement(PhysicalLocalStoreFactory::ROOT_NAME.c_str());
	elem->InsertEndChild(disk);
	XMLElement *disk1 = doc.NewElement(PhysicalLocalStoreFactory::ROOT_NAME.c_str());
	elem->InsertEndChild(disk1);
	XMLElement *disk2 = doc.NewElement(PhysicalLocalStoreFactory::ROOT_NAME.c_str());
	elem->InsertEndChild(disk2);

	Traits<MockPhysicalLocalStoreFactory>::Ptr mock = Traits<MockPhysicalLocalStoreFactory>::MakePtr();
	Traits<MockPhysicalLocalStore>::Ptr mockedDisk = Traits<MockPhysicalLocalStore>::MakePtr();
	PhysicalLocalStoreFactory::setInstance(mock);
	EXPECT_CALL(*mock, parseXML(_)).WillRepeatedly(Return(mockedDisk));
	EXPECT_CALL(*mockedDisk, setParent(_)).Times(3);
	EXPECT_CALL(*mockedDisk, getUUID()).WillOnce(Return("disk")).WillOnce(Return("disk1")).WillOnce(Return("disk2"));
	
	Traits<PhysicalHost>::Ptr object = factory.parseXML(elem);

	EXPECT_THAT(object->getLocalStores().size(), Eq(3));
	PhysicalLocalStoreFactory::setInstance(Traits<MockPhysicalLocalStoreFactory>::Ptr());
}

int main(int argc, char **argv) {
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
