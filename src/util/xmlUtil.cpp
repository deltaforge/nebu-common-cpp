
#include <string>
#include <sstream>

#include "nebu/util/exceptions.h"
#include "nebu/util/xmlUtil.h"

// Using declarations - tinyxml2
using tinyxml2::XMLAttribute;
using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;
using tinyxml2::XMLError;
// Using declarations - standard library
using std::make_shared;
using std::shared_ptr;
using std::string;
using std::stringstream;

namespace nebu
{
	namespace common
	{

		void XMLUtil::parseDocumentFromString(XMLDocument &doc, const string &xml)
		{
			XMLError err = doc.Parse(xml.c_str());
			if (err != XMLError::XML_SUCCESS) {
				throw XMLParseException("Failed to parse invalid XML");
			}
		}

		const XMLElement *XMLUtil::findChildElement(const XMLDocument &doc, const string &name, const bool mandatory)
		{
			const XMLElement *elem = doc.FirstChildElement(name.c_str());
			if (mandatory && elem == NULL) {
				stringstream ss;
				ss << "Could not find root element with name '" << name << "'";
				throw XMLParseException(ss.str());
			}
			return elem;
		}

		const XMLElement *XMLUtil::findChildElement(const XMLElement *elem, const string &name, const bool mandatory)
		{
			if (elem == NULL) {
				throw XMLParseException("Cannot find child element in NULL");
			}

			const XMLElement *child = elem->FirstChildElement(name.c_str());
			if (mandatory && child == NULL) {
				stringstream ss;
				ss << "Could not find child element with name '" << name << "' of parent '" <<
					elem->Name() << "'";
				throw XMLParseException(ss.str());
			}
			return child;
		}

		const XMLElement *XMLUtil::findNextSibling(const XMLElement *elem, const string &name, const bool mandatory)
		{
			if (elem == NULL) {
				throw XMLParseException("Cannot find sibling of NULL element");
			}

			const XMLElement *sibling = elem->NextSiblingElement(name.c_str());
			if (mandatory && sibling == NULL) {
				stringstream ss;
				ss << "Could not find sibling with name '" << name << "' of parent '" <<
					elem->Name() << "'";
				throw XMLParseException(ss.str());
			}
			return sibling;
		}

		const XMLAttribute *XMLUtil::findAttribute(const XMLElement *elem, const string &attr, const bool mandatory)
		{
			if (elem == NULL) {
				throw XMLParseException("Cannot find attribute of NULL element");
			}

			const XMLAttribute *attribute = elem->FindAttribute(attr.c_str());
			if (mandatory && attribute == NULL) {
				stringstream ss;
				ss << "Could not find attribute with name '" << attr << "' in element with name '" <<
					elem->Name() << "'";
				throw XMLParseException(ss.str());
			}
			return attribute;
		}

		void XMLUtil::verifyElementName(const XMLElement *elem, const string &expectedName)
		{
			if (elem == NULL) {
				throw XMLParseException("Cannot verify name of NULL element");
			}

			if (elem->Name() != expectedName) {
				stringstream ss;
				ss << "Element name '" << elem->Name() << "' does not match expected name '" <<
					expectedName << "'";
				throw XMLParseException(ss.str());
			}
		}

	}
}

