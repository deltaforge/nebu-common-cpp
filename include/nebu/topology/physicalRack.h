
#ifndef NEBU_PHYSICALRACK_H_
#define NEBU_PHYSICALRACK_H_

#include "nebu/identifiable.h"
#include "nebu/traits.h"

namespace nebu
{
	namespace common
	{

		class PhysicalHost;
		class PhysicalNetworkStore;
		class PhysicalDataCenter;

		/** Represents a rack in the physical topology. */
		class PhysicalRack : public Identifiable
		{
		public:
			/** Simple constructor that sets the uuid.
			 * Sets the uuid and inits the parent to NULL.
			 * @param[in] uuid to set.
			 */
			explicit PhysicalRack(const std::string &uuid) : Identifiable(uuid), parent(NULL) { }
			/** Simple default (empty) destructor. */
			virtual ~PhysicalRack() { }

			/** Gets the parent.
			 * @return the datacenter that is the parent.
			 */
			virtual PhysicalDataCenter *getParent()
			{
				return this->parent;
			}
			/** Sets the parent.
			 * @param[in] parent to set.
			 */
			virtual void setParent(PhysicalDataCenter *parent)
			{
				this->parent = parent;
			}

			/** Gets the hosts in this rack.
			 * @return the map of the hosts (uuid => physicalhost)
			 */
			virtual const Traits<PhysicalHost>::Map &getHosts() const
			{
				return this->hosts;
			}
			/** Sets the hosts in the rack.
			 * @param[in] hosts to set.
			 */
			virtual void setHosts(Traits<PhysicalHost>::Map hosts)
			{
				this->hosts = hosts;
			}	
			/** Adds a host to the rack.
			 * @param[in] host to add.
			 */
			virtual void addHost(Traits<PhysicalHost>::Ptr host);
			/** Removes a host from the rack, based on the uuid.
			 * @param[in] uuid of the host to remove.
			 */
			virtual void removeHost(const std::string &uuid)
			{
				this->hosts.erase(uuid);
			}
	
			/** Gets the stores in this rack.
			 * @return the map of the stores (uuid => physicalNetworkStore)
			 */
			virtual const Traits<PhysicalNetworkStore>::Map &getNetworkStores() const
			{
				return this->networkStores;
			}
			/** Sets the stores in this rack.
			 * @param[in] networkStores to set.
			 */
			virtual void setNetworkStores(Traits<PhysicalNetworkStore>::Map networkStores)
			{
				this->networkStores = networkStores;
			}	
			/** Add a store to this rack.
			 * @param[in] networkStore to add.
			 */
			virtual void addNetworkStore(Traits<PhysicalNetworkStore>::Ptr networkStore);
			/** Remove a store from this rack.
			 * @param[in] uuid of the store to remove.
			 */
			virtual void removeNetworkStore(const std::string &uuid)
			{
				this->networkStores.erase(uuid);
			}

		private:
			PhysicalDataCenter *parent;
			Traits<PhysicalHost>::Map hosts;
			Traits<PhysicalNetworkStore>::Map networkStores;
		};

	}
}

#endif

