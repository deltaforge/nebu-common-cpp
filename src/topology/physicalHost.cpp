
#include "nebu/topology/physicalHost.h"
#include "nebu/topology/physicalLocalStore.h"

namespace nebu
{
	namespace common
	{

		void PhysicalHost::addLocalStore(Traits<PhysicalLocalStore>::Ptr localStore)
		{
			if (localStore) {
				this->localStores[localStore->getUUID()] = localStore;
			}
		}

	}
}
