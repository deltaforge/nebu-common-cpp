
#ifndef NEBU_PHYSICALNETWORKSTOREFACTORY_H_
#define NEBU_PHYSICALNETWORKSTOREFACTORY_H_

#include "tinyxml2.h"

#include "nebu/topology/physicalNetworkStore.h"

namespace nebu
{
	namespace common
	{

		/**Creates a NetworkStore from xml.*/
		class PhysicalNetworkStoreFactory
		{
		public:
			static const std::string ROOT_NAME;
			static const std::string ATTR_ID;

			/** Simple default (empty) constructor. */
			PhysicalNetworkStoreFactory() { };
			/** Simple default (empty) destructor. */
			virtual ~PhysicalNetworkStoreFactory() { };

		  /** Parses a PhysicalNetworkStore from the xml.
			 * @param[in] elem to parse.
			 * @return a newly created PhysicalNetworkStore.
			 */
			virtual Traits<PhysicalNetworkStore>::Ptr parseXML(const tinyxml2::XMLElement *elem) const;

			/** Gets an instance of this class.
			 * Creates one if none has been found previously.
			 * @return an instance of this class.
			 */
			static std::shared_ptr<PhysicalNetworkStoreFactory> getInstance();

			/** Set an instance of this class to return with getInstance().
			 * Especially usefull for mocking.
			 * @param[in] instance to set.
			 */
			static void setInstance(std::shared_ptr<PhysicalNetworkStoreFactory> instance);

		private:
			static std::shared_ptr<PhysicalNetworkStoreFactory> instance;
		};

	}
}

#endif

