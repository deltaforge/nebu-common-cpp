
#include "nebu/topology/physicalDataCenterFactory.h"
#include "nebu/topology/physicalRootFactory.h"
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
		shared_ptr<PhysicalRootFactory> PhysicalRootFactory::instance;

		const string PhysicalRootFactory::ROOT_NAME = "root";
		const string PhysicalRootFactory::ATTR_ID = "id";

		shared_ptr<PhysicalRootFactory> PhysicalRootFactory::getInstance()
		{
			if (!PhysicalRootFactory::instance) {
				PhysicalRootFactory::setInstance(make_shared<PhysicalRootFactory>());
			}
			return PhysicalRootFactory::instance;
		}
		void PhysicalRootFactory::setInstance(std::shared_ptr<PhysicalRootFactory> instance)
		{
			PhysicalRootFactory::instance = instance;
		}

		Traits<PhysicalRoot>::Ptr PhysicalRootFactory::parseXML(const tinyxml2::XMLElement *elem)
		{
			XMLUtil::verifyElementName(elem, PhysicalRootFactory::ROOT_NAME);

			const XMLAttribute *idAttr = XMLUtil::findAttribute(elem, PhysicalRootFactory::ATTR_ID, XMLUtil::MANDATORY);
			Traits<PhysicalRoot>::Ptr root = Traits<PhysicalRoot>::MakePtr(idAttr->Value());

			const XMLElement *dataCenterElem = XMLUtil::findChildElement(elem, PhysicalDataCenterFactory::ROOT_NAME);
			while (dataCenterElem) {
				Traits<PhysicalDataCenter>::Ptr dataCenter = PhysicalDataCenterFactory::getInstance()->parseXML(dataCenterElem);
				root->addDataCenter(dataCenter);
				dataCenter->setParent(root.get());

				dataCenterElem = XMLUtil::findNextSibling(dataCenterElem, PhysicalDataCenterFactory::ROOT_NAME);
			}

			return root;
		}

	}
}
