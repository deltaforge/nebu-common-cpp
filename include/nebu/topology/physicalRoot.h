
#ifndef NEBU_PHYSICALROOT_H_
#define NEBU_PHYSICALROOT_H_

#include "nebu/identifiable.h"
#include "nebu/traits.h"

namespace nebu
{
	namespace common
	{

		class PhysicalDataCenter;

		/** Hold information on the root of the physical topology. */
		class PhysicalRoot : public Identifiable
		{
		public:
			/** Simple constructor that takes the uuid.
			 * Sets the uuid of the root.
			 * @param[in] uuid to set.
			 */
			explicit PhysicalRoot(const std::string &uuid) : Identifiable(uuid) { }
			/** Simple default (empty) destructor. */
			virtual ~PhysicalRoot() { }

			/** Gets the datacenters under this root.
			 * @return a map of the datacenters (uuid => PhysicalDataCenter)
			 */
			const Traits<PhysicalDataCenter>::Map &getDataCenters() const
			{
				return this->dataCenters;
			}
			/** Sets the datacenters under this root.
			 * @param[in] dataCenters to set.
			 */
			void setDataCenters(Traits<PhysicalDataCenter>::Map dataCenters)
			{
				this->dataCenters = dataCenters;
			}	
			/** Adds a datacenter to this root.
			 * @param[in] dataCenter to add.
			 */
			void addDataCenter(Traits<PhysicalDataCenter>::Ptr dataCenter);
			/** Removes a datacenter from this root.
			 * @param[in] uuid of the datacenter to remove.
			 */
			void removeDataCenter(const std::string &uuid)
			{
				this->dataCenters.erase(uuid);
			}

		private:
			Traits<PhysicalDataCenter>::Map dataCenters;
		};

	}
}

#endif


