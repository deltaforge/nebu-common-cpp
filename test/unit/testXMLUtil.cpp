
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "tinyxml2.h"

#include "nebu/util/exceptions.h"
#include "nebu/util/xmlUtil.h"

// Using declarations - tinyxml2
using tinyxml2::XMLAttribute;
using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;
// Using declarations - nebu-common
using nebu::common::XMLUtil;
using nebu::common::XMLParseException;

// Using declarations - gtest/gmock
using testing::Eq;
using testing::IsNull;
using testing::NotNull;
using testing::StrEq;

TEST(XMLUtilTest, testParseDocumentFromStringWithEmptyString) {
	try {
		XMLDocument doc;
		XMLUtil::parseDocumentFromString(doc, "");
		FAIL() << "Expected XMLParseException";
	} catch (XMLParseException &expected) {
		SUCCEED();
	}
}

TEST(XMLUtilTest, testParseDocumentFromStringWithInvalidXML) {
	try {
		XMLDocument doc;
		XMLUtil::parseDocumentFromString(doc, "<element>Missing end tag");
		FAIL() << "Expected XMLParseException";
	} catch (XMLParseException &expected) {
		SUCCEED();
	}
}

TEST(XMLUtilTest, testParseDocumentFromStringWithValidXML) {
	XMLDocument doc;
	XMLUtil::parseDocumentFromString(doc, "<rootElement />");

	EXPECT_THAT(doc.Error(), Eq(false));
}

TEST(XMLUtilTest, testFindChildElementOfDocForNonExistingNameNonMandatory) {
	XMLDocument doc;
	XMLUtil::parseDocumentFromString(doc, "<rootElement />");

	const XMLElement *childElement = XMLUtil::findChildElement(doc, "nonExistingChild");
	EXPECT_THAT(childElement, IsNull());
}

TEST(XMLUtilTest, testFindChildElementOfDocForNonExistingNameMandatory) {
	XMLDocument doc;
	XMLUtil::parseDocumentFromString(doc, "<rootElement />");

	try {
		XMLUtil::findChildElement(doc, "nonExistingChild", true);
		FAIL() << "Expected XMLParseException";
	} catch (XMLParseException &expected) {
		SUCCEED();
	}
}

TEST(XMLUtilTest, testFindChildElementOfDocForExistingName) {
	XMLDocument doc;
	XMLUtil::parseDocumentFromString(doc, "<rootElement />");

	const XMLElement *childElement = XMLUtil::findChildElement(doc, "rootElement", true);
	EXPECT_THAT(childElement, NotNull());
	EXPECT_THAT(childElement->Name(), StrEq("rootElement"));
}

TEST(XMLUtilTest, testFindChildElementOfNullElem) {
	try {
		XMLUtil::findChildElement(NULL, "nonExistentElement");
		FAIL() << "Expected XMLParseException";
	} catch (XMLParseException &expected) {
		SUCCEED();
	}
}

TEST(XMLUtilTest, testFindChildElementOfElemForNonExistingNameNonMandatory) {
	XMLDocument doc;
	XMLUtil::parseDocumentFromString(doc, "<rootElement><childElement /></rootElement>");

	const XMLElement *rootElement = XMLUtil::findChildElement(doc, "rootElement", true);
	const XMLElement *childElement = XMLUtil::findChildElement(rootElement, "nonExistentElement");
	EXPECT_THAT(childElement, IsNull());
}

TEST(XMLUtilTest, testFindChildElementOfElemForNonExistingNameMandatory) {
	XMLDocument doc;
	XMLUtil::parseDocumentFromString(doc, "<rootElement><childElement /></rootElement>");

	const XMLElement *rootElement = XMLUtil::findChildElement(doc, "rootElement", true);
	try {
		XMLUtil::findChildElement(rootElement, "nonExistentElement", true);
		FAIL() << "Expected XMLParseException";
	} catch (XMLParseException &expected) {
		SUCCEED();
	}
}

TEST(XMLUtilTest, testFindChildElementOfElemForExistingName) {
	XMLDocument doc;
	XMLUtil::parseDocumentFromString(doc, "<rootElement><childElement /></rootElement>");

	const XMLElement *rootElement = XMLUtil::findChildElement(doc, "rootElement", true);
	const XMLElement *childElement = XMLUtil::findChildElement(rootElement, "childElement", true);
	EXPECT_THAT(childElement, NotNull());
	EXPECT_THAT(childElement->Name(), StrEq("childElement"));
}

TEST(XMLUtilTest, testFindNextSiblingForNullElem) {
	try {
		XMLUtil::findNextSibling(NULL, "nonExistentElement");
		FAIL() << "Expected XMLParseException";
	} catch (XMLParseException &expected) {
		SUCCEED();
	}
}

TEST(XMLUtilTest, testFindNextSiblingForNonExistingNameNonMandatory) {
	XMLDocument doc;
	XMLUtil::parseDocumentFromString(doc, "<rootElement /><siblingElement />");

	const XMLElement *rootElement = XMLUtil::findChildElement(doc, "rootElement", true);
	const XMLElement *siblingElement = XMLUtil::findNextSibling(rootElement, "nonExistentElement");
	EXPECT_THAT(siblingElement, IsNull());
}

TEST(XMLUtilTest, testFindNextSiblingForNonExistingNameMandatory) {
	XMLDocument doc;
	XMLUtil::parseDocumentFromString(doc, "<rootElement /><siblingElement />");

	const XMLElement *rootElement = XMLUtil::findChildElement(doc, "rootElement", true);
	try {
		XMLUtil::findNextSibling(rootElement, "nonExistentElement", true);
		FAIL() << "Expected XMLParseException";
	} catch (XMLParseException &expected) {
		SUCCEED();
	}
}

TEST(XMLUtilTest, testFindNextSiblingForExistingName) {
	XMLDocument doc;
	XMLUtil::parseDocumentFromString(doc, "<rootElement /><siblingElement />");

	const XMLElement *rootElement = XMLUtil::findChildElement(doc, "rootElement", true);
	const XMLElement *siblingElement = XMLUtil::findNextSibling(rootElement, "siblingElement", true);
	EXPECT_THAT(siblingElement, NotNull());
	EXPECT_THAT(siblingElement->Name(), StrEq("siblingElement"));
}

TEST(XMLUtilTest, testFindNextSiblingChain) {
	XMLDocument doc;
	XMLUtil::parseDocumentFromString(doc, "<rootElement /><siblingElement /><siblingElement />");

	const XMLElement *rootElement = XMLUtil::findChildElement(doc, "rootElement", true);
	const XMLElement *siblingElementA = XMLUtil::findNextSibling(rootElement, "siblingElement", true);
	EXPECT_THAT(siblingElementA, NotNull());
	EXPECT_THAT(siblingElementA->Name(), StrEq("siblingElement"));

	const XMLElement *siblingElementB = XMLUtil::findNextSibling(siblingElementA, "siblingElement", true);
	EXPECT_THAT(siblingElementB, NotNull());
	EXPECT_THAT(siblingElementB->Name(), StrEq("siblingElement"));

	const XMLElement *siblingElementC = XMLUtil::findNextSibling(siblingElementB, "siblingElement");
	EXPECT_THAT(siblingElementC, IsNull());
}

TEST(XMLUtilTest, testFindAttributeOfNullElem) {
	try {
		XMLUtil::findAttribute(NULL, "nonExistentAttribute");
		FAIL() << "Expected XMLParseException";
	} catch (XMLParseException &expected) {
		SUCCEED();
	}
}

TEST(XMLUtilTest, testFindAttributeForNonExistingNameNonMandatory) {
	XMLDocument doc;
	XMLUtil::parseDocumentFromString(doc, "<rootElement attributeA='An attribute'/>");

	const XMLElement *rootElement = XMLUtil::findChildElement(doc, "rootElement", true);
	const XMLAttribute *attribute = XMLUtil::findAttribute(rootElement, "nonExistentAttribute");
	EXPECT_THAT(attribute, IsNull());
}

TEST(XMLUtilTest, testFindAttributeForNonExistingNameMandatory) {
	XMLDocument doc;
	XMLUtil::parseDocumentFromString(doc, "<rootElement attributeA='An attribute' />");

	const XMLElement *rootElement = XMLUtil::findChildElement(doc, "rootElement", true);
	try {
		XMLUtil::findAttribute(rootElement, "nonExistentAttribute", true);
		FAIL() << "Expected XMLParseException";
	} catch (XMLParseException &expected) {
		SUCCEED();
	}
}

TEST(XMLUtilTest, testFindAttributeForExistingName) {
	XMLDocument doc;
	XMLUtil::parseDocumentFromString(doc, "<rootElement attributeA='An attribute' />");

	const XMLElement *rootElement = XMLUtil::findChildElement(doc, "rootElement", true);
	const XMLAttribute *attribute = XMLUtil::findAttribute(rootElement, "attributeA", true);
	EXPECT_THAT(attribute, NotNull());
	EXPECT_THAT(attribute->Name(), StrEq("attributeA"));
	EXPECT_THAT(attribute->Value(), StrEq("An attribute"));
}

TEST(XMLUtilTest, testVerifyElementNameOfNullElem) {
	try {
		XMLUtil::verifyElementName(NULL, "incorrectName");
		FAIL() << "Expected XMLParseException";
	} catch (XMLParseException &expected) {
		SUCCEED();
	}
}

TEST(XMLUtilTest, testVerifyElementNameWithIncorrectName) {
	XMLDocument doc;
	XMLUtil::parseDocumentFromString(doc, "<rootElement />");
	const XMLElement *rootElement = XMLUtil::findChildElement(doc, "rootElement", true);

	try {
		XMLUtil::verifyElementName(rootElement, "incorrectName");
		FAIL() << "Expected XMLParseException";
	} catch (XMLParseException &expected) {
		SUCCEED();
	}
}

TEST(XMLUtilTest, testVerifyElementNameWithCorrectName) {
	XMLDocument doc;
	XMLUtil::parseDocumentFromString(doc, "<rootElement />");
	const XMLElement *rootElement = XMLUtil::findChildElement(doc, "rootElement", true);
	XMLUtil::verifyElementName(rootElement, "rootElement");
}

int main(int argc, char **argv) {
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
