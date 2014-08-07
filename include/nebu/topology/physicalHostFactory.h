
#ifndef NEBU_PHYSICALHOSTFACTORY_H_
#define NEBU_PHYSICALHOSTFACTORY_H_

#include "tinyxml2.h"

#include "nebu/topology/physicalHost.h"

namespace nebu
{
	namespace common
	{

		/**Creates a PhysicalHost from xml. */
		class PhysicalHostFactory
		{
		public:
			static const std::string ROOT_NAME;
			static const std::string ATTR_ID;

			/** Simple default (empty) constructor. */
			PhysicalHostFactory() { };
			/** Simple default (empty) destructor. */
			virtual ~PhysicalHostFactory() { };

			/** Parses the xml and creates a PhysicalHost.
			 * @param[in] elem to parse.
			 * @return the newly created PhysicalHost.
			 */
			virtual Traits<PhysicalHost>::Ptr parseXML(const tinyxml2::XMLElement *elem) const;

			
			/** Gets an instance of this class.
			 * Creates one if none has been found previously.
			 * @return an instance of this class.
			 */
			static std::shared_ptr<PhysicalHostFactory> getInstance();
			/** Set an instance of this class to return with getInstance().
			 * Especially usefull for mocking.
			 * @param[in] instance to set.
			 */
			static void setInstance(std::shared_ptr<PhysicalHostFactory> instance);

		private:
			static std::shared_ptr<PhysicalHostFactory> instance;
		};

	}
}

#endif

