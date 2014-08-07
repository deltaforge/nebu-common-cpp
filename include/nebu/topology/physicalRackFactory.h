
#ifndef NEBU_PHYSICALRACKFACTORY_H_
#define NEBU_PHYSICALRACKFACTORY_H_

#include "tinyxml2.h"

#include "nebu/topology/physicalRack.h"

namespace nebu
{
	namespace common
	{

		/** Creates Racks based on xml. */
		class PhysicalRackFactory
		{
		public:
			static const std::string ROOT_NAME;
			static const std::string ATTR_ID;

			/** Simple default (empty) constructor. */
			PhysicalRackFactory() { };
			/** Simple default (empty) destructor. */
			virtual ~PhysicalRackFactory() { };

		  /** Parses a PhysicalRack from the xml.
			 * @param[in] elem to parse.
			 * @return a newly created PhysicalRack.
			 */
			virtual Traits<PhysicalRack>::Ptr parseXML(const tinyxml2::XMLElement *elem) const;

			/** Gets an instance of this class.
			 * Creates one if none has been found previously.
			 * @return an instance of this class.
			 */
			static std::shared_ptr<PhysicalRackFactory> getInstance();
			/** Set an instance of this class to return with getInstance().
			 * Especially usefull for mocking.
			 * @param[in] instance to set.
			 */
			static void setInstance(std::shared_ptr<PhysicalRackFactory> instance);

		private:
			static std::shared_ptr<PhysicalRackFactory> instance;
		};

	}
}

#endif

