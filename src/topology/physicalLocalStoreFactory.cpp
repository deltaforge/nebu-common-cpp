
#include "nebu/topology/physicalLocalStoreFactory.h"
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
		shared_ptr<PhysicalLocalStoreFactory> PhysicalLocalStoreFactory::instance;

		const string PhysicalLocalStoreFactory::ROOT_NAME = "store";
		const string PhysicalLocalStoreFactory::ATTR_ID = "id";

		shared_ptr<PhysicalLocalStoreFactory> PhysicalLocalStoreFactory::getInstance()
		{
			if (!PhysicalLocalStoreFactory::instance) {
				PhysicalLocalStoreFactory::setInstance(make_shared<PhysicalLocalStoreFactory>());
			}
			return PhysicalLocalStoreFactory::instance;
		}
		void PhysicalLocalStoreFactory::setInstance(std::shared_ptr<PhysicalLocalStoreFactory> instance)
		{
			PhysicalLocalStoreFactory::instance = instance;
		}

		Traits<PhysicalLocalStore>::Ptr PhysicalLocalStoreFactory::parseXML(const tinyxml2::XMLElement *elem) const
		{
			XMLUtil::verifyElementName(elem, PhysicalLocalStoreFactory::ROOT_NAME);

			const XMLAttribute *idAttr = XMLUtil::findAttribute(elem, PhysicalLocalStoreFactory::ATTR_ID, XMLUtil::MANDATORY);
			Traits<PhysicalLocalStore>::Ptr localStore = Traits<PhysicalLocalStore>::MakePtr(idAttr->Value());

			return localStore;
		}

	}
}
