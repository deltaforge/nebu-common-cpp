#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "tinyxml2.h"

#include "nebu/topology/physicalRootFactory.h"
#include "mocks/mockPhysicalDataCenterFactory.h"
#include "mocks/mockPhysicalDataCenter.h"
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
using nebu::common::PhysicalRoot;
using nebu::common::PhysicalRootFactory;
using nebu::common::PhysicalDataCenterFactory;
using nebu::common::XMLParseException;
using nebu::common::XMLUtil;
using nebu::common::Traits;
using nebu::test::MockPhysicalDataCenter;
using nebu::test::MockPhysicalDataCenterFactory;

// Using declarations - gtest/gmock
using ::testing::Eq;
using ::testing::NotNull;
using ::testing::Contains;
using ::testing::Return;
using ::testing::_;

TEST(PhysicalRootFactoryTest, testGetInstance) {
		shared_ptr<PhysicalRootFactory> factory = PhysicalRootFactory::getInstance();
		EXPECT_THAT(factory.get(), NotNull());
}

TEST(PhysicalRootFactoryTest, testParseXMLNull) {
	PhysicalRootFactory factory;

	try {
		factory.parseXML(NULL);
		FAIL() << "Expected XMLParseException";
	} catch(XMLParseException &ex) {
		SUCCEED();
	}
}

TEST(PhysicalRootFactoryTest, testParseXMLEmptyXML) {
	PhysicalRootFactory factory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement("");

	try {
		factory.parseXML(elem);
		FAIL() << "Expected XMLParseException";
	} catch(XMLParseException &ex) {
		SUCCEED();
	}
}

TEST(PhysicalRootFactoryTest, testParseXMLWrongRoot) {
	PhysicalRootFactory factory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement("thisisnotthecorrectrootname");

	try {
		factory.parseXML(elem);
		FAIL() << "Expected XMLParseException";
	} catch(XMLParseException &ex) {
		SUCCEED();
	}
}

TEST(PhysicalRootFactoryTest, testParseXMLNoIDAttribute) {
	PhysicalRootFactory factory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement(PhysicalRootFactory::ROOT_NAME.c_str());

	try {
		factory.parseXML(elem);
		FAIL() << "Expected XMLParseException";
	} catch(XMLParseException &ex) {
		SUCCEED();
	}
}

TEST(PhysicalRootFactoryTest, testParseXMLCheckID) {
	PhysicalRootFactory factory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement(PhysicalRootFactory::ROOT_NAME.c_str());
	elem->SetAttribute(PhysicalRootFactory::ATTR_ID.c_str(), "id");

	Traits<PhysicalRoot>::Ptr object = factory.parseXML(elem);

	EXPECT_THAT(object->getUUID(), Eq("id"));
}

TEST(PhysicalRootFactoryTest, testParseXMLCheckNoDataCenters) {
	PhysicalRootFactory factory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement(PhysicalRootFactory::ROOT_NAME.c_str());
	elem->SetAttribute(PhysicalRootFactory::ATTR_ID.c_str(), "id");

	Traits<PhysicalRoot>::Ptr object = factory.parseXML(elem);

	EXPECT_THAT(object->getDataCenters().size(), Eq(0));
}

TEST(PhysicalRootFactoryTest, testParseXMLCheckSingleDataCenter) {
	PhysicalRootFactory factory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement(PhysicalRootFactory::ROOT_NAME.c_str());
	elem->SetAttribute(PhysicalRootFactory::ATTR_ID.c_str(), "id");
	XMLElement *dc = doc.NewElement(PhysicalDataCenterFactory::ROOT_NAME.c_str());
	elem->InsertEndChild(dc);

	Traits<MockPhysicalDataCenterFactory>::Ptr mock = Traits<MockPhysicalDataCenterFactory>::MakePtr();
	Traits<MockPhysicalDataCenter>::Ptr mockedDataCenter = Traits<MockPhysicalDataCenter>::MakePtr();
	PhysicalDataCenterFactory::setInstance(mock);
	EXPECT_CALL(*mock, parseXML(dc)).WillOnce(Return(mockedDataCenter));
	EXPECT_CALL(*mockedDataCenter, setParent(_));
	EXPECT_CALL(*mockedDataCenter, getUUID()).WillOnce(Return("dc"));
	
	Traits<PhysicalRoot>::Ptr object = factory.parseXML(elem);

	EXPECT_THAT(object->getDataCenters().size(), Eq(1));
	PhysicalDataCenterFactory::setInstance(Traits<MockPhysicalDataCenterFactory>::Ptr());
}

TEST(PhysicalRootFactoryTest, testParseXMLCheckTripleDataCenters) {
	PhysicalRootFactory factory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement(PhysicalRootFactory::ROOT_NAME.c_str());
	elem->SetAttribute(PhysicalRootFactory::ATTR_ID.c_str(), "id");
	XMLElement *dc = doc.NewElement(PhysicalDataCenterFactory::ROOT_NAME.c_str());
	elem->InsertEndChild(dc);
	XMLElement *dc1 = doc.NewElement(PhysicalDataCenterFactory::ROOT_NAME.c_str());
	elem->InsertEndChild(dc1);
	XMLElement *dc2 = doc.NewElement(PhysicalDataCenterFactory::ROOT_NAME.c_str());
	elem->InsertEndChild(dc2);

	Traits<MockPhysicalDataCenterFactory>::Ptr mock = Traits<MockPhysicalDataCenterFactory>::MakePtr();
	Traits<MockPhysicalDataCenter>::Ptr mockedDataCenter = Traits<MockPhysicalDataCenter>::MakePtr();
	PhysicalDataCenterFactory::setInstance(mock);
	EXPECT_CALL(*mock, parseXML(_)).WillRepeatedly(Return(mockedDataCenter));
	EXPECT_CALL(*mockedDataCenter, setParent(_)).Times(3);
	EXPECT_CALL(*mockedDataCenter, getUUID()).WillOnce(Return("dc")).WillOnce(Return("dc1")).WillOnce(Return("dc2"));
	
	Traits<PhysicalRoot>::Ptr object = factory.parseXML(elem);

	EXPECT_THAT(object->getDataCenters().size(), Eq(3));
	PhysicalDataCenterFactory::setInstance(Traits<MockPhysicalDataCenterFactory>::Ptr());
}

int main(int argc, char **argv) {
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
