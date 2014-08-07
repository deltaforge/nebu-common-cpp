
#ifndef NEBU_RESTCLIENT_H_
#define NEBU_RESTCLIENT_H_

#include "restclient.h"

#include <memory>
#include <string>

namespace nebu
{
	namespace common
	{

		class RestClientAdapter
		{
		public:
			RestClientAdapter() { }
			virtual ~RestClientAdapter() { }

			virtual RestClient::response get(const std::string& url) const
			{
				return RestClient::get(url);
			}

			virtual RestClient::response post(const std::string& url, const std::string& ctype,
						const std::string& data) const
			{
				return RestClient::post(url, ctype, data);
			}

			virtual RestClient::response put(const std::string& url, const std::string& ctype,
						const std::string& data) const
			{
				return RestClient::put(url, ctype, data);
			}

			virtual RestClient::response del(const std::string& url) const
			{
				return RestClient::del(url);
			}

			static std::shared_ptr<RestClientAdapter> getInstance();

		private:
			static std::shared_ptr<RestClientAdapter> instance;
		};

	}
}

#endif
