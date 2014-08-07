#ifndef NEBUTEST_MOCKRESTCLIENTADAPTER_H_
#define NEBUTEST_MOCKRESTCLIENTADAPTER_H_

#include "gmock/gmock.h"

#include "nebu/restClientAdapter.h"

namespace nebu
{
	namespace test
	{

		class MockRestClientAdapter : public nebu::common::RestClientAdapter
		{
		public:
			MOCK_CONST_METHOD1(get, RestClient::response(const std::string& url));
			MOCK_CONST_METHOD3(post, RestClient::response(const std::string& url,
					const std::string& ctype, const std::string& data));
			MOCK_CONST_METHOD3(put, RestClient::response(const std::string& url,
					const std::string& ctype, const std::string& data));
			MOCK_CONST_METHOD1(del, RestClient::response(const std::string& url));
		};

	}
}

#endif
