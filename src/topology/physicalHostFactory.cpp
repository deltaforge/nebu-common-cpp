
#include "nebu/topology/physicalHostFactory.h"
#include "nebu/topology/physicalLocalStoreFactory.h"
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
		shared_ptr<PhysicalHostFactory> PhysicalHostFactory::instance;

		const string PhysicalHostFactory::ROOT_NAME = "host";
		const string PhysicalHostFactory::ATTR_ID = "id";

		shared_ptr<PhysicalHostFactory> PhysicalHostFactory::getInstance()
		{
			if (!PhysicalHostFactory::instance) {
				PhysicalHostFactory::setInstance(make_shared<PhysicalHostFactory>());
			}
			return PhysicalHostFactory::instance;
		}
		void PhysicalHostFactory::setInstance(std::shared_ptr<PhysicalHostFactory> instance)
		{
			PhysicalHostFactory::instance = instance;
		}

		Traits<PhysicalHost>::Ptr PhysicalHostFactory::parseXML(const tinyxml2::XMLElement *elem) const
		{
			XMLUtil::verifyElementName(elem, PhysicalHostFactory::ROOT_NAME);

			const XMLAttribute *idAttr = XMLUtil::findAttribute(elem, PhysicalHostFactory::ATTR_ID, XMLUtil::MANDATORY);
			Traits<PhysicalHost>::Ptr host = Traits<PhysicalHost>::MakePtr(idAttr->Value());

			const XMLElement *localStoreElem = XMLUtil::findChildElement(elem, PhysicalLocalStoreFactory::ROOT_NAME);
			while (localStoreElem) {
				Traits<PhysicalLocalStore>::Ptr localStore = PhysicalLocalStoreFactory::getInstance()->parseXML(localStoreElem);
				host->addLocalStore(localStore);
				localStore->setParent(host.get());

				localStoreElem = XMLUtil::findNextSibling(localStoreElem, PhysicalLocalStoreFactory::ROOT_NAME);
			}

			return host;
		}

	}
}
