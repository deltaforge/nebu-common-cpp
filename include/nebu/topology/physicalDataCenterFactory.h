
#ifndef NEBU_PHYSICALDATACENTERFACTORY_H_
#define NEBU_PHYSICALDATACENTERFACTORY_H_

#include "tinyxml2.h"

#include "nebu/topology/physicalDataCenter.h"

namespace nebu
{
	namespace common
	{

		/**Creates a DataCenter from xml.*/
		class PhysicalDataCenterFactory
		{
		public:
			static const std::string ROOT_NAME;
			static const std::string ATTR_ID;

			/** Simple default constructor.*/
			PhysicalDataCenterFactory() { };

			/** Simple default destructor.*/
			virtual ~PhysicalDataCenterFactory() { };

		  /** Parses a PhysicalDataCenter from the xml.
			 * @param[in] elem to parse.
			 * @return a newly created PhysicalDataCenter.
			 */
			virtual Traits<PhysicalDataCenter>::Ptr parseXML(const tinyxml2::XMLElement *elem) const;


			/** Gets an instance of this class.
			 * Creates one if none has been found previously.
			 * @return an instance of this class.
			 */
			static std::shared_ptr<PhysicalDataCenterFactory> getInstance();

			/** Set an instance of this class to return with getInstance().
			 * Especially usefull for mocking.
			 * @param[in] instance to set.
			 */
			static void setInstance(std::shared_ptr<PhysicalDataCenterFactory> instance);

		private:
			static std::shared_ptr<PhysicalDataCenterFactory> instance;
		};

	}
}

#endif

