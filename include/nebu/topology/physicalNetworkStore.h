
#ifndef NEBU_PHYSICALNETWORKSTORE_H_
#define NEBU_PHYSICALNETWORKSTORE_H_

#include "nebu/topology/physicalStore.h"
#include "nebu/traits.h"

namespace nebu
{
	namespace common
	{

		class PhysicalRack;
		
		/** Holds all information on a network store in the physical topology. */
		class PhysicalNetworkStore : public PhysicalStore
		{
		public:
			/** Simple constructor that takes an uuid.
			 * Sets the uuid and resets the parent to NULL.
			 * @param[in] uuid to set.
			 */
			explicit PhysicalNetworkStore(const std::string &uuid) : PhysicalStore(uuid), parent(NULL) { }
			/** Simple default (empty) destructor. */
			virtual ~PhysicalNetworkStore() { }

			/** Gets the parent.
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

		private:
			PhysicalRack *parent;
		};

	}
}

#endif


