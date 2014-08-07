
#ifndef NEBU_PHYSICALSTORE_H_
#define NEBU_PHYSICALSTORE_H_

#include "nebu/identifiable.h"

namespace nebu
{
	namespace common
	{
		
		/** Holds information of a store of a physical topology. */
		class PhysicalStore : public Identifiable
		{
		public:
			/** Simple constructor that sets the uuid.
			 * @param[in] uuid to set.
			 */
			explicit PhysicalStore(const std::string &uuid) : Identifiable(uuid) { }
			/** Simple default (empty) destructor. */
			virtual ~PhysicalStore() { }

		};

	}
}

#endif

