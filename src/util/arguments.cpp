
#include "nebu/util/arguments.h"

#include <sstream>

using std::string;
using std::stringstream;

namespace nebu
{
	namespace common
	{

		void Arguments::throwIfNull(const void * const argument, const std::string &argumentName,
				const std::string &functionName)
		{
			if (argument == NULL) {
				stringstream ss;
				ss << "Argument '" << argumentName << "' must not be null in function '" <<
					functionName << "'.";
				throw IllegalArgumentException(ss.str());
			}
		}

	}
}

