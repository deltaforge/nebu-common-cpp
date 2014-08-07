
#ifndef NEBU_STRINGUTIL_H_
#define NEBU_STRINGUTIL_H_

#include <string>

namespace nebu
{
	namespace common
	{

		class StringUtil
		{
		public:
			static std::string concatWithDelimiter(std::string A,
					std::string B, const char delimiter);
		};

	}
}

#endif

