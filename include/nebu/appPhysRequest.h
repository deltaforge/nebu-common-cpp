
#ifndef NEBU_APPPHYSREQUEST_H_
#define NEBU_APPPHYSREQUEST_H_

#include "nebu/nebuClient.h"
#include "nebu/traits.h"

namespace nebu
{
	namespace common
	{

		class PhysicalRoot;

		class AppPhysRequest
		{
		public:
			AppPhysRequest(std::shared_ptr<NebuClient> client, const std::string &app);
			virtual ~AppPhysRequest() { };

			virtual Traits<PhysicalRoot>::Ptr getPhysicalTopology() const;

			static const std::string APP_URI;
			static const std::string PHYS_URI;
		protected:
			std::string appURI;
			std::shared_ptr<NebuClient> client;
		};

	}
}

#endif
