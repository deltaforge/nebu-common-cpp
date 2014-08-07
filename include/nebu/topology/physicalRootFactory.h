
#ifndef NEBU_PHYSICALROOTFACTORY_H_
#define NEBU_PHYSICALROOTFACTORY_H_

#include "tinyxml2.h"

#include "nebu/topology/physicalRoot.h"

namespace nebu
{
	namespace common
	{

		/** Creates a PhysicalRoot from the xml. */
		class PhysicalRootFactory
		{
		public:
			static const std::string ROOT_NAME;
			static const std::string ATTR_ID;

			/** Simple default (empty) constructor. */
			PhysicalRootFactory() { };
			/** Simple default (empty) destructor. */
			virtual ~PhysicalRootFactory() { };

		  /** Parses a PhysicalRoot from the xml.
			 * @param[in] elem to parse.
			 * @return a newly created PhysicalRoot.
			 */
			virtual Traits<PhysicalRoot>::Ptr parseXML(const tinyxml2::XMLElement *elem);

			/** Gets an instance of this class.
			 * Creates one if none has been found previously.
			 * @return an instance of this class.
			 */
			static std::shared_ptr<PhysicalRootFactory> getInstance();
			/** Set an instance of this class to return with getInstance().
			 * Especially usefull for mocking.
			 * @param[in] instance to set.
			 */
			static void setInstance(std::shared_ptr<PhysicalRootFactory> instance);

		private:
			static std::shared_ptr<PhysicalRootFactory> instance;
		};

	}
}

#endif

