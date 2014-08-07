
#ifndef NEBU_VIRTUALMACHINE_H_
#define NEBU_VIRTUALMACHINE_H_

#include "nebu/identifiable.h"

namespace nebu
{
	namespace common
	{

		/** Enumeration of the different status possiblities for a VM */
		enum class VMStatus
		{
			ON,
			OFF,
			UNKNOWN
		};
	
		/** Holds information on a VirtualMachine */
		class VirtualMachine : public Identifiable
		{
		public:
			/** Simple constructor.
			 * Sets the uuid and defaults the status to UNKNOWN.
			 * @param[in] uuid to set.
			 */
			explicit VirtualMachine(const std::string &uuid) : Identifiable(uuid),
					hostname(""), status(VMStatus::UNKNOWN), physicalHostID("") { }
			/** Simple default destructor */
			virtual ~VirtualMachine() { }

			/** Sets the hostname.
			 * @param[in] hostname to set.
			 */
			void setHostname(const std::string &hostname);
			/** Sets the status.
			 * @param[in] status to set.
			 */
			void setStatus(const VMStatus status);
			/** Sets the physical host id.
			 * @param[in] physicalHostID to set.
			 */
			void setPhysicalHostID(const std::string &physicalHostID);
			/** Sets the physical store id.
			 * @param[in] physicalStoreID to set.
			 */
			void setPhysicalStoreID(const std::string &physicalStoreID);

			/** Gets the hostname.
			 * @return the hostname.
			 */
			inline std::string getHostname() const { return this->hostname; }
			/** Gets the status.
			 * @return the status.
			 */
			inline VMStatus getStatus() const { return this->status; }
			/** Gets the physical host id.
			 * @return the physical host id.
			 */
			inline std::string getPhysicalHostID() const { return this->physicalHostID; }
			/** Gets the physical store id.
			 * @return the phyiscal store id.
			 */
			inline std::string getPhysicalStoreID() const { return this->physicalStoreID; }

		private:
			std::string hostname;
			VMStatus status;
			std::string physicalHostID;
			std::string physicalStoreID;
		};
			
	}
}

#endif

