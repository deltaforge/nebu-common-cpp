
#ifndef NEBU_IDENTIFIABLE_H_
#define NEBU_IDENTIFIABLE_H_

#include <string>

namespace nebu
{
	namespace common
	{
		/** Base class for everything that needs to be uniquely identifiable.
		 * Provides a getUUID() function.
		 */
		class Identifiable {
		public:
			/** Constructor that sets the uuid. */
			explicit Identifiable(const std::string &uuid) { this->uuid = uuid; }
			/** Simple default constructor.*/
			virtual ~Identifiable() { }

			/** Simple getter.
			 * @return the uuid of this identifiable.
			 */
			virtual std::string getUUID() { return this->uuid; }
		
			/** Considers them equal if uuids are equal.
			 * @param[in] other to compare it with.
			 * @return true iff uuids are equal.
			 */
			virtual inline bool operator== (const Identifiable &other) const {
				return (this->uuid == other.uuid);
			}

			/** Considers them equal if uuids are equal.
			 * @param[in] other to compare it with.
			 * @return false iff uuids are equal.
			 */
			virtual inline bool operator!= (const Identifiable &other) const {
				return !(*this == other);
			}

		protected:
			std::string uuid;
		};

	}
}

#endif

