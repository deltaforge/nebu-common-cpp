
#include "nebu/topology/physicalNetworkStoreFactory.h"
#include "nebu/util/xmlUtil.h"

// Using declarations - tinyxml2
using tinyxml2::XMLAttribute;
// Using declarations - standard library
using std::make_shared;
using std::shared_ptr;
using std::string;

namespace nebu
{
	namespace common
	{
		shared_ptr<PhysicalNetworkStoreFactory> PhysicalNetworkStoreFactory::instance;

		const string PhysicalNetworkStoreFactory::ROOT_NAME = "store";
		const string PhysicalNetworkStoreFactory::ATTR_ID = "id";

		shared_ptr<PhysicalNetworkStoreFactory> PhysicalNetworkStoreFactory::getInstance()
		{
			if (!PhysicalNetworkStoreFactory::instance) {
				PhysicalNetworkStoreFactory::setInstance(make_shared<PhysicalNetworkStoreFactory>());
			}
			return PhysicalNetworkStoreFactory::instance;
		}
		void PhysicalNetworkStoreFactory::setInstance(std::shared_ptr<PhysicalNetworkStoreFactory> instance)
		{
			PhysicalNetworkStoreFactory::instance = instance;
		}

		Traits<PhysicalNetworkStore>::Ptr PhysicalNetworkStoreFactory::parseXML(const tinyxml2::XMLElement *elem) const
		{
			XMLUtil::verifyElementName(elem, PhysicalNetworkStoreFactory::ROOT_NAME);

			const XMLAttribute *idAttr = XMLUtil::findAttribute(elem, PhysicalNetworkStoreFactory::ATTR_ID, XMLUtil::MANDATORY);
			Traits<PhysicalNetworkStore>::Ptr localStore = Traits<PhysicalNetworkStore>::MakePtr(idAttr->Value());

			return localStore;
		}

	}
}
