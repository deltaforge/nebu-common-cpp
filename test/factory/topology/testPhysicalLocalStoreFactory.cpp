#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "tinyxml2.h"

#include "nebu/topology/physicalLocalStoreFactory.h"
#include "nebu/util/exceptions.h"
#include "nebu/util/xmlUtil.h"

// Using declarations - tinyxml2
using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;
using std::string;
using std::shared_ptr;
// Using declarations - nebu-common
using nebu::common::PhysicalLocalStore;
using nebu::common::PhysicalLocalStoreFactory;
using nebu::common::XMLParseException;
using nebu::common::XMLUtil;
using nebu::common::Traits;

// Using declarations - gtest/gmock
using ::testing::Eq;
using ::testing::NotNull;

TEST(PhysicalLocalStoreFactoryTest, testGetInstance) {
		shared_ptr<PhysicalLocalStoreFactory> factory = PhysicalLocalStoreFactory::getInstance();
		EXPECT_THAT(factory.get(), NotNull());
}

TEST(PhysicalLocalStoreFactoryTest, testParseXMLNull) {
	PhysicalLocalStoreFactory physicalLocalStoreFactory;

	try {
		physicalLocalStoreFactory.parseXML(NULL);
		FAIL() << "Expected XMLParseException";
	} catch(XMLParseException &ex) {
		SUCCEED();
	}
}

TEST(PhysicalLocalStoreFactoryTest, testParseXMLEmptyXML) {
	PhysicalLocalStoreFactory physicalLocalStoreFactory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement("");

	try {
		physicalLocalStoreFactory.parseXML(elem);
		FAIL() << "Expected XMLParseException";
	} catch(XMLParseException &ex) {
		SUCCEED();
	}
}

TEST(PhysicalLocalStoreFactoryTest, testParseXMLWrongRoot) {
	PhysicalLocalStoreFactory physicalLocalStoreFactory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement("thisisnotthecorrectrootname");

	try {
		physicalLocalStoreFactory.parseXML(elem);
		FAIL() << "Expected XMLParseException";
	} catch(XMLParseException &ex) {
		SUCCEED();
	}
}

TEST(PhysicalLocalStoreFactoryTest, testParseXMLNoIDAttribute) {
	PhysicalLocalStoreFactory physicalLocalStoreFactory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement(PhysicalLocalStoreFactory::ROOT_NAME.c_str());

	try {
		physicalLocalStoreFactory.parseXML(elem);
		FAIL() << "Expected XMLParseException";
	} catch(XMLParseException &ex) {
		SUCCEED();
	}
}

TEST(PhysicalLocalStoreFactoryTest, testParseXMLCheckID) {
	PhysicalLocalStoreFactory physicalLocalStoreFactory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement(PhysicalLocalStoreFactory::ROOT_NAME.c_str());
	elem->SetAttribute(PhysicalLocalStoreFactory::ATTR_ID.c_str(), "id");

	Traits<PhysicalLocalStore>::Ptr vm = physicalLocalStoreFactory.parseXML(elem);

	EXPECT_THAT(vm->getUUID(), Eq("id"));
}


int main(int argc, char **argv) {
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
