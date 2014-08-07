
#include "nebu/topology/physicalDataCenterFactory.h"
#include "nebu/topology/physicalRackFactory.h"
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
		shared_ptr<PhysicalDataCenterFactory> PhysicalDataCenterFactory::instance;

		const string PhysicalDataCenterFactory::ROOT_NAME = "dataCenter";
		const string PhysicalDataCenterFactory::ATTR_ID = "id";

		shared_ptr<PhysicalDataCenterFactory> PhysicalDataCenterFactory::getInstance()
		{
			if (!PhysicalDataCenterFactory::instance) {
				PhysicalDataCenterFactory::setInstance(make_shared<PhysicalDataCenterFactory>());
			}
			return PhysicalDataCenterFactory::instance;
		}
		void PhysicalDataCenterFactory::setInstance(std::shared_ptr<PhysicalDataCenterFactory> instance)
		{
			PhysicalDataCenterFactory::instance = instance;
		}

		Traits<PhysicalDataCenter>::Ptr PhysicalDataCenterFactory::parseXML(const tinyxml2::XMLElement *elem) const
		{
			XMLUtil::verifyElementName(elem, PhysicalDataCenterFactory::ROOT_NAME);

			const XMLAttribute *idAttr = XMLUtil::findAttribute(elem, PhysicalDataCenterFactory::ATTR_ID, XMLUtil::MANDATORY);
			Traits<PhysicalDataCenter>::Ptr dataCenter = Traits<PhysicalDataCenter>::MakePtr(idAttr->Value());

			const XMLElement *rackElem = XMLUtil::findChildElement(elem, PhysicalRackFactory::ROOT_NAME);
			while (rackElem) {
				Traits<PhysicalRack>::Ptr rack = PhysicalRackFactory::getInstance()->parseXML(rackElem);
				dataCenter->addRack(rack);
				rack->setParent(dataCenter.get());

				rackElem = XMLUtil::findNextSibling(rackElem, PhysicalRackFactory::ROOT_NAME);
			}

			return dataCenter;
		}

	}
}
