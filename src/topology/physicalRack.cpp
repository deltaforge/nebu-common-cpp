
#include "nebu/topology/physicalHost.h"
#include "nebu/topology/physicalRack.h"
#include "nebu/topology/physicalNetworkStore.h"

namespace nebu
{
	namespace common
	{

		void PhysicalRack::addHost(Traits<PhysicalHost>::Ptr host)
		{
			if (host) {
				this->hosts[host->getUUID()] =  host;
			}
		}

		void PhysicalRack::addNetworkStore(Traits<PhysicalNetworkStore>::Ptr networkStore)
		{
			if (networkStore) {
				this->networkStores[networkStore->getUUID()] = networkStore;
			}
		}

	}
}
