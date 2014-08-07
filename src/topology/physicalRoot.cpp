
#include "nebu/topology/physicalDataCenter.h"
#include "nebu/topology/physicalRoot.h"

namespace nebu
{
	namespace common
	{

		void PhysicalRoot::addDataCenter(Traits<PhysicalDataCenter>::Ptr dataCenter)
		{
			if (dataCenter) {
				this->dataCenters[dataCenter->getUUID()] = dataCenter;
			}
		}

	}
}
