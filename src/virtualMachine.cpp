
#include "nebu/virtualMachine.h"

// Using declarations - standard library
using std::string;

namespace nebu
{
	namespace common
	{

		void VirtualMachine::setHostname(const string &hostname)
		{
			this->hostname = hostname;
		}
		
		void VirtualMachine::setStatus(const VMStatus status)
		{
			this->status = status;
		}

		void VirtualMachine::setPhysicalHostID(const string &physicalHostID)
		{
			this->physicalHostID = physicalHostID;
		}

		void VirtualMachine::setPhysicalStoreID(const string &physicalStoreID)
		{
			this->physicalStoreID = physicalStoreID;
		}

	}
}
