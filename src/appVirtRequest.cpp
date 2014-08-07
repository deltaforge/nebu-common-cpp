
#include "tinyxml2.h"

#include "nebu/appVirtRequest.h"
#include "nebu/util/exceptions.h"
#include "nebu/util/stringUtil.h"
#include "nebu/util/xmlUtil.h"

// Using declarations - tinyxml2
using tinyxml2::XMLAttribute;
using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;
// Using declarations - standard library
using std::shared_ptr;
using std::string;
using std::vector;

namespace nebu
{
	namespace common
	{

		const string AppVirtRequest::APP_URI = "/app";
		const string AppVirtRequest::VIRT_URI = "/virt";

		AppVirtRequest::AppVirtRequest(shared_ptr<NebuClient> client, const string &app) :
			client(client)
		{
			this->appURI = StringUtil::concatWithDelimiter(AppVirtRequest::APP_URI, app, '/');
		}

		VirtualMachine AppVirtRequest::getVirtualMachine(const std::string &uuid) const
		{
			string uri = StringUtil::concatWithDelimiter(this->appURI, AppVirtRequest::VIRT_URI, '/');
			uri = StringUtil::concatWithDelimiter(uri, uuid, '/');
			NebuClient::Response response = this->client->performGET(uri);

			if (response.status_code != 200) {
				throw NebuServerException("Server did not respond with status OK");
			}

			try {
				XMLDocument doc;
				XMLUtil::parseDocumentFromString(doc, response.body);
				const XMLElement *rootElem = XMLUtil::findChildElement(doc, VirtualMachineFactory::ROOT_NAME);
				VirtualMachine vm = VirtualMachineFactory::getInstance()->parseXML(rootElem);
				return vm;
			} catch (XMLParseException &ex) {
				throw WRAP_NEBU_SERVER_EXCEPTION(ex, "XMLParseException");
			}
		}

		vector<string> AppVirtRequest::getVirtualMachineIDs() const
		{
			string uri = StringUtil::concatWithDelimiter(this->appURI, AppVirtRequest::VIRT_URI, '/');
			NebuClient::Response response = this->client->performGET(uri);

			if (response.status_code != 200) {
				throw NebuServerException("Server did not respond with status OK");
			}

			try {
				XMLDocument doc;
				XMLUtil::parseDocumentFromString(doc, response.body);
				const XMLElement *rootElem = XMLUtil::findChildElement(doc, VirtualMachineFactory::ROOT_NAME_LIST, XMLUtil::MANDATORY);

				vector<string> res;
				const XMLElement *vmElem = XMLUtil::findChildElement(rootElem, VirtualMachineFactory::ROOT_NAME);
				for (; vmElem != NULL; vmElem = XMLUtil::findNextSibling(vmElem, VirtualMachineFactory::ROOT_NAME)) {
					const XMLAttribute *id = XMLUtil::findAttribute(vmElem, VirtualMachineFactory::ATTR_ID, XMLUtil::MANDATORY);
					res.push_back(id->Value());
				}
				return res;
			} catch (XMLParseException &ex) {
				throw WRAP_NEBU_SERVER_EXCEPTION(ex, "XMLParseException");
			}
		}

	}
}

