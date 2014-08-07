
#ifndef NEBU_ARGUMENTS_H_
#define NEBU_ARGUMENTS_H_

#include <string>

#include "nebu/util/exceptions.h"

#define NEBU_THROWIFNULL(arg) \
	nebu::common::Arguments::throwIfNull(arg, #arg, __PRETTY_FUNCTION__)

namespace nebu
{
	namespace common
	{

		class Arguments
		{
		public:
			static void throwIfNull(const void * const argument, const std::string &argumentName,
				const std::string &functionName);
		};

	}
}

#endif

