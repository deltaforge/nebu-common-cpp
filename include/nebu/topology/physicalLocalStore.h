
#ifndef NEBU_PHYSICALLOCALSTORE_H_
#define NEBU_PHYSICALLOCALSTORE_H_

#include "nebu/topology/physicalStore.h"
#include "nebu/traits.h"

namespace nebu
{
	namespace common
	{

		class PhysicalHost;
		
		/** Holds information to on LocalStores in the physical topology **/
		class PhysicalLocalStore : public PhysicalStore
		{
		public:
			/** Simple constructor that takes an uuid
			 * Sets the uuid and sets the parent to NULL.
			 * @param[in] uuid to set.
			 */
			explicit PhysicalLocalStore(const std::string &uuid) : PhysicalStore(uuid), parent(NULL) { }
			/** Simple (empty) destructor */
			virtual ~PhysicalLocalStore() { }

			/** Gets the parent.
			 * @return the host that is the parent.
			 */
			virtual PhysicalHost *getParent() const
			{
				return this->parent;
			}
			/** Sets the parent.
			 * @param[in] parent to set.
			 */
			virtual void setParent(PhysicalHost *parent)
			{
				this->parent = parent;
			}

		private:
			PhysicalHost *parent;
		};

	}
}

#endif



