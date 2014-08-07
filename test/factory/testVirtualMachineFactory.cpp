
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "tinyxml2.h"

#include "nebu/virtualMachineFactory.h"
#include "nebu/util/exceptions.h"
#include "nebu/util/xmlUtil.h"

// Using declarations - tinyxml2
using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;
// Using declarations - standard library
using std::make_shared;
using std::shared_ptr;
using std::string;
// Using declarations - nebu-common
using nebu::common::VirtualMachine;
using nebu::common::VirtualMachineFactory;
using nebu::common::VMStatus;
using nebu::common::XMLParseException;
using nebu::common::XMLUtil;

// Using declarations - gtest/gmock
using ::testing::Eq;
using ::testing::NotNull;

TEST(VirtualMachineFactoryTest, testStatusFromStringON) {
	VirtualMachineFactory virtualMachineFactory;
	string status = VirtualMachineFactory::STATUS_ON;

	EXPECT_THAT(virtualMachineFactory.statusFromString(status), Eq(VMStatus::ON));
}

TEST(VirtualMachineFactoryTest, testStatusFromStringOFF) {
	VirtualMachineFactory virtualMachineFactory;
	string status = VirtualMachineFactory::STATUS_OFF;

	EXPECT_THAT(virtualMachineFactory.statusFromString(status), Eq(VMStatus::OFF));
}

TEST(VirtualMachineFactoryTest, testStatusFromStringUNKNOWN) {
	VirtualMachineFactory virtualMachineFactory;
	string status = "invalid status string";

	EXPECT_THAT(virtualMachineFactory.statusFromString(status), Eq(VMStatus::UNKNOWN));
}

TEST(VirtualMachineFactoryTest, testParseXMLNull) {
	VirtualMachineFactory virtualMachineFactory;

	try {
		virtualMachineFactory.parseXML(NULL);
		FAIL() << "Expected XMLParseException";
	} catch(XMLParseException &ex) {
		SUCCEED();
	}
}

TEST(VirtualMachineFactoryTest, testParseXMLEmptyXML) {
	VirtualMachineFactory virtualMachineFactory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement("");

	try {
		virtualMachineFactory.parseXML(elem);
		FAIL() << "Expected XMLParseException";
	} catch(XMLParseException &ex) {
		SUCCEED();
	}
}

TEST(VirtualMachineFactoryTest, testParseXMLWrongRoot) {
	VirtualMachineFactory virtualMachineFactory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement("thisisnotthecorrectrootname");

	try {
		virtualMachineFactory.parseXML(elem);
		FAIL() << "Expected XMLParseException";
	} catch(XMLParseException &ex) {
		SUCCEED();
	}
}

TEST(VirtualMachineFactoryTest, testParseXMLNoIDAttribute) {
	VirtualMachineFactory virtualMachineFactory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement(VirtualMachineFactory::ROOT_NAME.c_str());

	try {
		virtualMachineFactory.parseXML(elem);
		FAIL() << "Expected XMLParseException";
	} catch(XMLParseException &ex) {
		SUCCEED();
	}
}

TEST(VirtualMachineFactoryTest, testParseXMLCheckID) {
	VirtualMachineFactory virtualMachineFactory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement(VirtualMachineFactory::ROOT_NAME.c_str());
	elem->SetAttribute(VirtualMachineFactory::ATTR_ID.c_str(), "id");

	VirtualMachine vm = virtualMachineFactory.parseXML(elem);

	EXPECT_THAT(vm.getUUID(), Eq("id"));
}

TEST(VirtualMachineFactoryTest, testParseXMLCheckHostname) {
	VirtualMachineFactory virtualMachineFactory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement(VirtualMachineFactory::ROOT_NAME.c_str());
	XMLElement *hostElem = doc.NewElement(VirtualMachineFactory::TAG_HOSTNAME.c_str());
	const string hostname = "myhostname.example.org";
	hostElem->SetText(hostname.c_str());
	elem->InsertEndChild(hostElem);
	elem->SetAttribute(VirtualMachineFactory::ATTR_ID.c_str(), "id");

	VirtualMachine vm = virtualMachineFactory.parseXML(elem);

	EXPECT_THAT(vm.getHostname(), Eq(hostname));
}

TEST(VirtualMachineFactoryTest, testParseXMLCheckStatus) {
	VirtualMachineFactory virtualMachineFactory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement(VirtualMachineFactory::ROOT_NAME.c_str());
	XMLElement *statusElem = doc.NewElement(VirtualMachineFactory::TAG_STATUS.c_str());
	elem->SetAttribute(VirtualMachineFactory::ATTR_ID.c_str(), "id");
	statusElem->SetText("OFF");
	elem->InsertEndChild(statusElem);

	VirtualMachine vm = virtualMachineFactory.parseXML(elem);

	EXPECT_THAT(vm.getStatus(), Eq(VMStatus::OFF));
}

TEST(VirtualMachineFactoryTest, testParseXMLCheckPhysHost) {
	VirtualMachineFactory virtualMachineFactory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement(VirtualMachineFactory::ROOT_NAME.c_str());
	XMLElement *hostElem = doc.NewElement(VirtualMachineFactory::TAG_PHYSICALHOST.c_str());
	const string hostname = "myhostname.example.org";
	hostElem->SetAttribute(VirtualMachineFactory::ATTR_ID.c_str(), hostname.c_str());
	elem->InsertEndChild(hostElem);
	elem->SetAttribute(VirtualMachineFactory::ATTR_ID.c_str(), "id");

	VirtualMachine vm = virtualMachineFactory.parseXML(elem);

	EXPECT_THAT(vm.getPhysicalHostID(), Eq(hostname));
}

TEST(VirtualMachineFactoryTest, testParseXMLCheckPhysStore) {
	VirtualMachineFactory virtualMachineFactory;
	XMLDocument doc;
	XMLElement *elem = doc.NewElement(VirtualMachineFactory::ROOT_NAME.c_str());
	XMLElement *hostElem = doc.NewElement(VirtualMachineFactory::TAG_PHYSICALSTORE.c_str());
	const string hostname = "myhostname.example.org";
	hostElem->SetAttribute(VirtualMachineFactory::ATTR_ID.c_str(), hostname.c_str());
	elem->InsertEndChild(hostElem);
	elem->SetAttribute(VirtualMachineFactory::ATTR_ID.c_str(), "id");

	VirtualMachine vm = virtualMachineFactory.parseXML(elem);

	EXPECT_THAT(vm.getPhysicalStoreID(), Eq(hostname));
}

TEST(VirtualMachineFactoryTest, testGetInstance) {
		shared_ptr<VirtualMachineFactory> factory = VirtualMachineFactory::getInstance();
		EXPECT_THAT(factory.get(), NotNull());
}

int main(int argc, char **argv) {
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
