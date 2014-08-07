
#ifndef NEBU_PHYSICALLOCALSTOREFACTORY_H_
#define NEBU_PHYSICALLOCALSTOREFACTORY_H_

#include "tinyxml2.h"

#include "nebu/topology/physicalLocalStore.h"

namespace nebu
{
	namespace common
	{

		/**Creates a LocalStore from xml.*/
		class PhysicalLocalStoreFactory
		{
		public:
			static const std::string ROOT_NAME;
			static const std::string ATTR_ID;

			/** Simple default (empty) constructor. */
			PhysicalLocalStoreFactory() { };
			/** Simple default (empty) destructor. */
			virtual ~PhysicalLocalStoreFactory() { };

		  /** Parses a PhysicalLocalStore from the xml.
			 * @param[in] elem to parse.
			 * @return a newly created PhysicalLocalStore.
			 */
			virtual Traits<PhysicalLocalStore>::Ptr parseXML(const tinyxml2::XMLElement *elem) const;

			/** Gets an instance of this class.
			 * Creates one if none has been found previously.
			 * @return an instance of this class.
			 */
			static std::shared_ptr<PhysicalLocalStoreFactory> getInstance();
			/** Set an instance of this class to return with getInstance().
			 * Especially usefull for mocking.
			 * @param[in] instance to set.
			 */
			static void setInstance(std::shared_ptr<PhysicalLocalStoreFactory> instance);

		private:
			static std::shared_ptr<PhysicalLocalStoreFactory> instance;
		};

	}
}

#endif

