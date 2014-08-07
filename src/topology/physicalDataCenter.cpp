
#include "nebu/topology/physicalDataCenter.h"
#include "nebu/topology/physicalRack.h"

namespace nebu
{
	namespace common
	{

		void PhysicalDataCenter::addRack(Traits<PhysicalRack>::Ptr rack)
		{
			if (rack) {
				this->racks[rack->getUUID()] = rack;
			}
		}

	}
}
