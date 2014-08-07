
#include "tinyxml2.h"

#include "nebu/virtualMachineFactory.h"

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

		shared_ptr<VirtualMachineFactory> VirtualMachineFactory::instance;

		const string VirtualMachineFactory::ROOT_NAME_LIST = "virtualmachines";
		const string VirtualMachineFactory::ROOT_NAME = "virtualmachine";
		const string VirtualMachineFactory::ATTR_ID = "id";
		const string VirtualMachineFactory::TAG_HOSTNAME = "hostname";
		const string VirtualMachineFactory::TAG_PHYSICALHOST = "host";
		const string VirtualMachineFactory::TAG_PHYSICALSTORE = "store";
		const string VirtualMachineFactory::TAG_STATUS = "status";

		const string VirtualMachineFactory::STATUS_ON = "ON";
		const string VirtualMachineFactory::STATUS_OFF = "OFF";

		shared_ptr<VirtualMachineFactory> VirtualMachineFactory::getInstance()
		{
			if (!VirtualMachineFactory::instance) {
				VirtualMachineFactory::instance = make_shared<VirtualMachineFactory>();
			}
			return VirtualMachineFactory::instance;
		}

		VirtualMachine VirtualMachineFactory::parseXML(const XMLElement *elem)
		{
			XMLUtil::verifyElementName(elem, VirtualMachineFactory::ROOT_NAME);

			const XMLAttribute *idAttr = XMLUtil::findAttribute(elem,
					VirtualMachineFactory::ATTR_ID, XMLUtil::MANDATORY);
			VirtualMachine vm(idAttr->Value());

			const XMLElement *hostnameElem = XMLUtil::findChildElement(elem, VirtualMachineFactory::TAG_HOSTNAME);
			if (hostnameElem) {
				vm.setHostname(hostnameElem->GetText());
			}

			const XMLElement *statusElem = XMLUtil::findChildElement(elem, VirtualMachineFactory::TAG_STATUS);
			if (statusElem) {
				vm.setStatus(this->statusFromString(statusElem->GetText()));
			}

			const XMLElement *hostElem = XMLUtil::findChildElement(elem, VirtualMachineFactory::TAG_PHYSICALHOST);
			if (hostElem) {
				idAttr = XMLUtil::findAttribute(hostElem, VirtualMachineFactory::ATTR_ID, XMLUtil::MANDATORY);
				vm.setPhysicalHostID(idAttr->Value());
			}

			const XMLElement *storeElem = XMLUtil::findChildElement(elem, VirtualMachineFactory::TAG_PHYSICALSTORE);
			if (storeElem) {
				idAttr = XMLUtil::findAttribute(storeElem, VirtualMachineFactory::ATTR_ID, XMLUtil::MANDATORY);
				vm.setPhysicalStoreID(idAttr->Value());
			}

			return vm;
		}

		VMStatus VirtualMachineFactory::statusFromString(const string &status)
		{
			if (strcasecmp(status.c_str(), VirtualMachineFactory::STATUS_ON.c_str()) == 0) {
				return VMStatus::ON;
			} else if (strcasecmp(status.c_str(), VirtualMachineFactory::STATUS_OFF.c_str()) == 0) {
				return VMStatus::OFF;
			} else {
				return VMStatus::UNKNOWN;
			}
		}

	}
}
