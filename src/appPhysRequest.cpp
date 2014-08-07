
#include "nebu/appPhysRequest.h"
#include "nebu/topology/physicalRootFactory.h"
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

namespace nebu
{
	namespace common
	{

		const string AppPhysRequest::APP_URI = "/app";
		const string AppPhysRequest::PHYS_URI = "/phys";

		AppPhysRequest::AppPhysRequest(shared_ptr<NebuClient> client, const string &app) :
			client(client)
		{
			this->appURI = StringUtil::concatWithDelimiter(AppPhysRequest::APP_URI, app, '/');
		}

		Traits<PhysicalRoot>::Ptr AppPhysRequest::getPhysicalTopology() const
		{
			string uri = StringUtil::concatWithDelimiter(this->appURI, AppPhysRequest::PHYS_URI, '/');
			NebuClient::Response response = this->client->performGET(uri);

			if (response.status_code != 200) {
				throw NebuServerException("Server did not respond with status OK");
			}

			try {
				XMLDocument doc;
				XMLUtil::parseDocumentFromString(doc, response.body);
				const XMLElement *rootElem = XMLUtil::findChildElement(doc, PhysicalRootFactory::ROOT_NAME);
				return PhysicalRootFactory::getInstance()->parseXML(rootElem);
			} catch (XMLParseException &ex) {
				throw WRAP_NEBU_SERVER_EXCEPTION(ex, "XMLParseException");
			}
		}

	}
}
