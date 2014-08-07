
#ifndef NEBU_PHYSICALHOST_H_
#define NEBU_PHYSICALHOST_H_

#include "nebu/identifiable.h"
#include "nebu/traits.h"

namespace nebu
{
	namespace common
	{

		class PhysicalRack;
		class PhysicalLocalStore;
		
		/** Holds the information on a host of the physical topology. */
		class PhysicalHost : public Identifiable
		{
		public:
			/** Simple constructor.
			 * Sets the uuid as specified and inits the parent to NULL.
			 * @param[in] uuid to set.
			 */
			explicit PhysicalHost(const std::string &uuid) : Identifiable(uuid), parent(NULL) { }
			/** Simple destructor. */
			virtual ~PhysicalHost() { }

			/** Getter for the parent.
			 * @return the rack that is the parent.
			 */
			virtual PhysicalRack *getParent() const
			{
				return this->parent;
			}
			/** Sets the parent.
			 * @param[in] parent to set.
			 */
			virtual void setParent(PhysicalRack *parent)
			{
				this->parent = parent;
			}

			/** Gets the local stores of the rack.
			 * @return a map of the localstores (uuid => PhysicalLocalStore).
			 */
			virtual const Traits<PhysicalLocalStore>::Map &getLocalStores() const
			{
				return this->localStores;
			}
			/** Sets the local stores of the rack.
			 * @param[in] localStores to set.
			 */
			virtual void setLocalStores(Traits<PhysicalLocalStore>::Map localStores)
			{
				this->localStores = localStores;
			}	
			/** Adds a local store to the rack.
			 * @param[in] localStore to add.
			 */
			virtual void addLocalStore(Traits<PhysicalLocalStore>::Ptr localStore);
			/** Removes the local store with the given uuid.
			 * @param[in] uuid of the store to remove.
			 */
			virtual void removeLocalStore(const std::string &uuid)
			{
				this->localStores.erase(uuid);
			}

		private:
			PhysicalRack *parent;
			Traits<PhysicalLocalStore>::Map localStores;
		};

	}
}

#endif

