
#ifndef NEBU_PHYSICALDATACENTER_H_
#define NEBU_PHYSICALDATACENTER_H_

#include "nebu/identifiable.h"
#include "nebu/traits.h"

namespace nebu
{
	namespace common
	{

		class PhysicalRoot;
		class PhysicalRack;
		
		/** Holds the information on a DataCenter in the physical topology.*/
		class PhysicalDataCenter : public Identifiable
		{
		public:
			/** Simple constructor.
			 * Sets the uuid and sets the parent to NULL.
			 * @param[in] uuid to set.
			 */
			explicit PhysicalDataCenter(const std::string &uuid) : Identifiable(uuid), parent(NULL) { }
			/** Simple default constructor. */
			virtual ~PhysicalDataCenter() { }

			/** Gets the parent.
			 * @return the root that is the parent.
			 */
			virtual PhysicalRoot *getParent() const
			{
				return this->parent;
			}
			/** Sets the parent.
			 * @param[in] parent to set.
			 */
			virtual	void setParent(PhysicalRoot *parent)
			{
				this->parent = parent;
			}

			/** Gets all the racks as a map.
			 * @return the racks in a map (uuid => rack).
			 */
			virtual	const Traits<PhysicalRack>::Map &getRacks() const
			{
				return this->racks;
			}
			/** Sets the racks as a map.
			 * @param[in] racks to set.
			 */
			virtual	void setRacks(Traits<PhysicalRack>::Map racks)
			{
				this->racks = racks;
			}	
			/** Adds a rack to the datacenter.
			 * @param[in] rack to add.
			 */
			virtual	void addRack(Traits<PhysicalRack>::Ptr rack);
			/** Removes the rack identified by the uuid.
			 * @param[in] uuid of the rack to remove.
			 */
			virtual	void removeRack(const std::string &uuid)
			{
				this->racks.erase(uuid);
			}

		private:
			PhysicalRoot *parent;
			Traits<PhysicalRack>::Map racks;
		};

	}
}

#endif

