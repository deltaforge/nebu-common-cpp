
#include "nebu/restClientAdapter.h"

// Using declarations - standard library
using std::make_shared;
using std::shared_ptr;

namespace nebu
{
	namespace common
	{

		shared_ptr<RestClientAdapter> RestClientAdapter::instance;

		shared_ptr<RestClientAdapter> RestClientAdapter::getInstance()
		{
			if (!RestClientAdapter::instance) {
				RestClientAdapter::instance = make_shared<RestClientAdapter>();
			}
			return RestClientAdapter::instance;
		}

	}
}
