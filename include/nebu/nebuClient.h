
#ifndef NEBU_NEBUCLIENT_H_
#define NEBU_NEBUCLIENT_H_

#include "nebu/restClientAdapter.h"

#include <memory>
#include <string>

namespace nebu
{
	namespace common
	{

		class NebuClient
		{
		public:
			struct Response
			{
				int status_code;
				std::string body;
			};

			NebuClient(std::shared_ptr<RestClientAdapter> restClient, const std::string &baseURI);
			virtual ~NebuClient() { }

			// NOT IMPLEMENTED:
			//NebuClient(shared_ptr<RestClientAdapter> restClient, const std::string &baseURI,
			//		const std::string &username, const std::string &password);

			virtual Response performGET(const std::string &URI) const;

		private:
			std::shared_ptr<RestClientAdapter> restClient;
			std::string baseURI;
		};

	}
}

#endif

