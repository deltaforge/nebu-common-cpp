
#ifndef NEBU_XMLUTIL_H_
#define NEBU_XMLUTIL_H_

#include "tinyxml2.h"

#include <memory>
#include <string>

namespace nebu
{
	namespace common
	{

		class XMLUtil
		{
		public:
			static const bool NOT_MANDATORY = false;
			static const bool MANDATORY = true;

			static void parseDocumentFromString(tinyxml2::XMLDocument &doc, const std::string &xml);
			static const tinyxml2::XMLElement *findChildElement(const tinyxml2::XMLDocument &doc,
					const std::string &name, const bool mandatory = NOT_MANDATORY);
			static const tinyxml2::XMLElement *findChildElement(const tinyxml2::XMLElement *elem,
					const std::string &name, const bool mandatory = NOT_MANDATORY);
			static const tinyxml2::XMLElement *findNextSibling(const tinyxml2::XMLElement *elem,
					const std::string &name, const bool mandatory = NOT_MANDATORY);
			static const tinyxml2::XMLAttribute *findAttribute(const tinyxml2::XMLElement *elem,
					const std::string &attr, const bool mandatory = NOT_MANDATORY);

			static void verifyElementName(const tinyxml2::XMLElement *elem, const std::string &expectedName);
		};

	}
}

#endif

