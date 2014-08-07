#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "tinyxml2.h"

#include "nebu/topology/physicalNetworkStoreFactory.h"
#include "nebu/util/exceptions.h"
#include "nebu/util/xmlUtil.h"

// Using declarations - tinyxml2
using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;
using std::string;
using std::shared_ptr;
// Using declarations - nebu-common
using nebu::common::PhysicalNetworkStore;
using nebu::common::PhysicalNetworkStoreFactory;
using nebu::common::XMLParseException;
using nebu::common::XMLUtil;
using nebu::common::Traits;

// Using declarations - gtest/gmock
using ::testing::Eq;
using ::testing::NotNull;

TEST(PhysicalNetworkStoreFactoryTest, testGetInstance) {
		shared_ptr<PhysicalNetworkStoreFactory> factory = PhysicalNetworkStoreFactory::getInstance();
		EXPECT_THAT(factory.get(), NotNull());
}

TEST(PhysicalNetworkStoreFactoryTest, testParseXMLNull) {
	PhysicalNetworkStoreFactory physicalNetworkStoreFactory;

	try {
		physicalNetworkStoreFactory.parseXML(NULL);
		FAIL() << "Expected XMLParseException";
	} catch(XMLParseException &ex) {
		SUCCEED();
	}
}

TEST(PhysicalNetworkStoreFactoryTest, testParseXMLEmptyXML) {
	PhysicalNetworkStoreFactory physicalNetworkStoreFactory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement("");

	try {
		physicalNetworkStoreFactory.parseXML(elem);
		FAIL() << "Expected XMLParseException";
	} catch(XMLParseException &ex) {
		SUCCEED();
	}
}

TEST(PhysicalNetworkStoreFactoryTest, testParseXMLWrongRoot) {
	PhysicalNetworkStoreFactory physicalNetworkStoreFactory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement("thisisnotthecorrectrootname");

	try {
		physicalNetworkStoreFactory.parseXML(elem);
		FAIL() << "Expected XMLParseException";
	} catch(XMLParseException &ex) {
		SUCCEED();
	}
}

TEST(PhysicalNetworkStoreFactoryTest, testParseXMLNoIDAttribute) {
	PhysicalNetworkStoreFactory physicalNetworkStoreFactory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement(PhysicalNetworkStoreFactory::ROOT_NAME.c_str());

	try {
		physicalNetworkStoreFactory.parseXML(elem);
		FAIL() << "Expected XMLParseException";
	} catch(XMLParseException &ex) {
		SUCCEED();
	}
}

TEST(PhysicalNetworkStoreFactoryTest, testParseXMLCheckID) {
	PhysicalNetworkStoreFactory physicalNetworkStoreFactory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement(PhysicalNetworkStoreFactory::ROOT_NAME.c_str());
	elem->SetAttribute(PhysicalNetworkStoreFactory::ATTR_ID.c_str(), "id");

	Traits<PhysicalNetworkStore>::Ptr vm = physicalNetworkStoreFactory.parseXML(elem);

	EXPECT_THAT(vm->getUUID(), Eq("id"));
}


int main(int argc, char **argv) {
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
