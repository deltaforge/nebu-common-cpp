
#include "nebu/topology/physicalHostFactory.h"
#include "nebu/topology/physicalRackFactory.h"
#include "nebu/topology/physicalNetworkStoreFactory.h"
#include "nebu/util/xmlUtil.h"

// Using declarations - tinyxml2
using tinyxml2::XMLAttribute;
using tinyxml2::XMLElement;
// Using declarations - standard library
using std::make_shared;
using std::shared_ptr;
using std::string;

namespace nebu
{
	namespace common
	{
		shared_ptr<PhysicalRackFactory> PhysicalRackFactory::instance;

		const string PhysicalRackFactory::ROOT_NAME = "rack";
		const string PhysicalRackFactory::ATTR_ID = "id";

		shared_ptr<PhysicalRackFactory> PhysicalRackFactory::getInstance()
		{
			if (!PhysicalRackFactory::instance) {
				PhysicalRackFactory::setInstance(make_shared<PhysicalRackFactory>());
			}
			return PhysicalRackFactory::instance;
		}
		void PhysicalRackFactory::setInstance(std::shared_ptr<PhysicalRackFactory> instance)
		{
			PhysicalRackFactory::instance = instance;
		}

		Traits<PhysicalRack>::Ptr PhysicalRackFactory::parseXML(const tinyxml2::XMLElement *elem) const
		{
			XMLUtil::verifyElementName(elem, PhysicalRackFactory::ROOT_NAME);

			const XMLAttribute *idAttr = XMLUtil::findAttribute(elem, PhysicalRackFactory::ATTR_ID, XMLUtil::MANDATORY);
			Traits<PhysicalRack>::Ptr rack = Traits<PhysicalRack>::MakePtr(idAttr->Value());

			const XMLElement *networkStoreElem = XMLUtil::findChildElement(elem, PhysicalNetworkStoreFactory::ROOT_NAME);
			while (networkStoreElem) {
				Traits<PhysicalNetworkStore>::Ptr networkStore = PhysicalNetworkStoreFactory::getInstance()->parseXML(networkStoreElem);
				rack->addNetworkStore(networkStore);
				networkStore->setParent(rack.get());

				networkStoreElem = XMLUtil::findNextSibling(networkStoreElem, PhysicalNetworkStoreFactory::ROOT_NAME);
			}

			const XMLElement *hostElem = XMLUtil::findChildElement(elem, PhysicalHostFactory::ROOT_NAME);
			while (hostElem) {
				Traits<PhysicalHost>::Ptr host = PhysicalHostFactory::getInstance()->parseXML(hostElem);
				rack->addHost(host);
				host->setParent(rack.get());

				hostElem = XMLUtil::findNextSibling(hostElem, PhysicalHostFactory::ROOT_NAME);
			}

			return rack;
		}

	}
}
