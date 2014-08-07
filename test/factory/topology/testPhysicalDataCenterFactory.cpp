#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "tinyxml2.h"

#include "nebu/topology/physicalDataCenterFactory.h"
#include "mocks/mockPhysicalRackFactory.h"
#include "mocks/mockPhysicalRack.h"
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
using nebu::common::PhysicalDataCenter;
using nebu::common::PhysicalDataCenterFactory;
using nebu::common::PhysicalRackFactory;
using nebu::common::XMLParseException;
using nebu::common::XMLUtil;
using nebu::common::Traits;
using nebu::test::MockPhysicalRack;
using nebu::test::MockPhysicalRackFactory;

// Using declarations - gtest/gmock
using ::testing::Eq;
using ::testing::NotNull;
using ::testing::Contains;
using ::testing::Return;
using ::testing::_;

TEST(PhysicalDataCenterFactoryTest, testGetInstance) {
		shared_ptr<PhysicalDataCenterFactory> factory = PhysicalDataCenterFactory::getInstance();
		EXPECT_THAT(factory.get(), NotNull());
}

TEST(PhysicalDataCenterFactoryTest, testParseXMLNull) {
	PhysicalDataCenterFactory factory;

	try {
		factory.parseXML(NULL);
		FAIL() << "Expected XMLParseException";
	} catch(XMLParseException &ex) {
		SUCCEED();
	}
}

TEST(PhysicalDataCenterFactoryTest, testParseXMLEmptyXML) {
	PhysicalDataCenterFactory factory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement("");

	try {
		factory.parseXML(elem);
		FAIL() << "Expected XMLParseException";
	} catch(XMLParseException &ex) {
		SUCCEED();
	}
}

TEST(PhysicalDataCenterFactoryTest, testParseXMLWrongRoot) {
	PhysicalDataCenterFactory factory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement("thisisnotthecorrectrootname");

	try {
		factory.parseXML(elem);
		FAIL() << "Expected XMLParseException";
	} catch(XMLParseException &ex) {
		SUCCEED();
	}
}

TEST(PhysicalDataCenterFactoryTest, testParseXMLNoIDAttribute) {
	PhysicalDataCenterFactory factory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement(PhysicalDataCenterFactory::ROOT_NAME.c_str());

	try {
		factory.parseXML(elem);
		FAIL() << "Expected XMLParseException";
	} catch(XMLParseException &ex) {
		SUCCEED();
	}
}

TEST(PhysicalDataCenterFactoryTest, testParseXMLCheckID) {
	PhysicalDataCenterFactory factory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement(PhysicalDataCenterFactory::ROOT_NAME.c_str());
	elem->SetAttribute(PhysicalDataCenterFactory::ATTR_ID.c_str(), "id");

	Traits<PhysicalDataCenter>::Ptr object = factory.parseXML(elem);

	EXPECT_THAT(object->getUUID(), Eq("id"));
}

TEST(PhysicalDataCenterFactoryTest, testParseXMLCheckNoRacks) {
	PhysicalDataCenterFactory factory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement(PhysicalDataCenterFactory::ROOT_NAME.c_str());
	elem->SetAttribute(PhysicalDataCenterFactory::ATTR_ID.c_str(), "id");

	Traits<PhysicalDataCenter>::Ptr object = factory.parseXML(elem);

	EXPECT_THAT(object->getRacks().size(), Eq(0));
}

TEST(PhysicalDataCenterFactoryTest, testParseXMLCheckSingleDisk) {
	PhysicalDataCenterFactory factory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement(PhysicalDataCenterFactory::ROOT_NAME.c_str());
	elem->SetAttribute(PhysicalDataCenterFactory::ATTR_ID.c_str(), "id");
	XMLElement *disk = doc.NewElement(PhysicalRackFactory::ROOT_NAME.c_str());
	elem->InsertEndChild(disk);

	Traits<MockPhysicalRackFactory>::Ptr mock = Traits<MockPhysicalRackFactory>::MakePtr();
	Traits<MockPhysicalRack>::Ptr mockedDisk = Traits<MockPhysicalRack>::MakePtr();
	PhysicalRackFactory::setInstance(mock);
	EXPECT_CALL(*mock, parseXML(disk)).WillOnce(Return(mockedDisk));
	EXPECT_CALL(*mockedDisk, setParent(_));
	EXPECT_CALL(*mockedDisk, getUUID()).WillOnce(Return("disk"));
	
	Traits<PhysicalDataCenter>::Ptr object = factory.parseXML(elem);

	EXPECT_THAT(object->getRacks().size(), Eq(1));
	PhysicalRackFactory::setInstance(Traits<MockPhysicalRackFactory>::Ptr());
}

TEST(PhysicalDataCenterFactoryTest, testParseXMLCheckTripleRacks) {
	PhysicalDataCenterFactory factory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement(PhysicalDataCenterFactory::ROOT_NAME.c_str());
	elem->SetAttribute(PhysicalDataCenterFactory::ATTR_ID.c_str(), "id");
	XMLElement *disk = doc.NewElement(PhysicalRackFactory::ROOT_NAME.c_str());
	elem->InsertEndChild(disk);
	XMLElement *disk1 = doc.NewElement(PhysicalRackFactory::ROOT_NAME.c_str());
	elem->InsertEndChild(disk1);
	XMLElement *disk2 = doc.NewElement(PhysicalRackFactory::ROOT_NAME.c_str());
	elem->InsertEndChild(disk2);

	Traits<MockPhysicalRackFactory>::Ptr mock = Traits<MockPhysicalRackFactory>::MakePtr();
	Traits<MockPhysicalRack>::Ptr mockedDisk = Traits<MockPhysicalRack>::MakePtr();
	PhysicalRackFactory::setInstance(mock);
	EXPECT_CALL(*mock, parseXML(_)).WillRepeatedly(Return(mockedDisk));
	EXPECT_CALL(*mockedDisk, setParent(_)).Times(3);
	EXPECT_CALL(*mockedDisk, getUUID()).WillOnce(Return("disk")).WillOnce(Return("disk1")).WillOnce(Return("disk2"));
	
	Traits<PhysicalDataCenter>::Ptr object = factory.parseXML(elem);

	EXPECT_THAT(object->getRacks().size(), Eq(3));
	PhysicalRackFactory::setInstance(Traits<MockPhysicalRackFactory>::Ptr());
}

int main(int argc, char **argv) {
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
