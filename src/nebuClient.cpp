
#include "restclient.h"

#include "nebu/nebuClient.h"
#include "nebu/util/stringUtil.h"

// Using declarations - standard library
using std::shared_ptr;
using std::string;

namespace nebu
{
	namespace common
	{

		NebuClient::NebuClient(shared_ptr<RestClientAdapter> restClient, const string &baseURI) :
				restClient(restClient), baseURI(baseURI)
		{

		}

		NebuClient::Response NebuClient::performGET(const string &URI) const
		{
			string uri = StringUtil::concatWithDelimiter(this->baseURI, URI, '/');
			RestClient::response response = this->restClient->get(uri);
			NebuClient::Response res;

			res.status_code = response.code;
			res.body = response.body;

			return res;
		}

	}
}
