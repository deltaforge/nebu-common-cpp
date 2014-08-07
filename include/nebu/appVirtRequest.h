
#ifndef NEBU_APPVIRTREQUEST_H_
#define NEBU_APPVIRTREQUEST_H_

#include <memory>
#include <string>
#include <vector>

#include "nebu/nebuClient.h"
#include "nebu/virtualMachine.h"
#include "nebu/virtualMachineFactory.h"
#include "nebu/util/xmlUtil.h"

namespace nebu
{
	namespace common
	{

		class AppVirtRequest
		{
		public:
			AppVirtRequest(std::shared_ptr<NebuClient> client, const std::string &app);
			virtual ~AppVirtRequest() { };

			virtual VirtualMachine getVirtualMachine(const std::string &uuid) const;
			virtual std::vector<std::string> getVirtualMachineIDs() const;

			static const std::string APP_URI;
			static const std::string VIRT_URI;
		protected:
			std::string appURI;
			std::shared_ptr<NebuClient> client;
		};

	}
}

#endif

