
#ifndef NEBU_VIRTUALMACHINEFACTORY_H_
#define NEBU_VIRTUALMACHINEFACTORY_H_

#include <memory>

#include "tinyxml2.h"

#include "nebu/virtualMachine.h"
#include "nebu/util/xmlUtil.h"

namespace nebu
{
	namespace common
	{

		/**
		 * Factory that parses xml and creates VirtualMachine objects.
		 */
		class VirtualMachineFactory
		{
		public:

			static const std::string ROOT_NAME_LIST;
			static const std::string ROOT_NAME;
			static const std::string ATTR_ID;
			static const std::string TAG_HOSTNAME;
			static const std::string TAG_STATUS;
			static const std::string TAG_PHYSICALHOST;
			static const std::string TAG_PHYSICALSTORE;
			static const std::string STATUS_ON;
			static const std::string STATUS_OFF;

			/** Simple default (empty) constructor. */
			explicit VirtualMachineFactory() { }
			
			/** Parses XML to a VirtualMachine object.
			 * @param[in] elem to parse.
			 * @return the parsed VirtualMachine object.
			 */
			VirtualMachine parseXML(const tinyxml2::XMLElement *elem);
			/** Converts a std::string to a VMStatus object.
			 * @param[in] status string to convert.
			 * @return the converted status, or Unknown if it maches nothing.
			 */
			VMStatus statusFromString(const std::string &status);

			/** Gets an instance of the class. 
			 * @return an instance of the class, creating one if needed.
			 */
			static std::shared_ptr<VirtualMachineFactory> getInstance();

		private:
			static std::shared_ptr<VirtualMachineFactory> instance;
		};

	}
}

#endif

