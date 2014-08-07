
#include "nebu/util/exceptions.h"
#include "nebu/util/stringUtil.h"

// Using declarations - standard library
using std::string;

namespace nebu
{
	namespace common
	{

		string StringUtil::concatWithDelimiter(string A, string B, const char delimiter)
		{
			if (delimiter == '\0') {
				throw IllegalArgumentException("SpringUtil::concatWithDelimiter: Delimiter must not be '\\0'.");
			}

			// Remove trailing delimiters
			while (A.length() > 0 && A.at(A.length() - 1) == delimiter) {
				A.erase(A.end() - 1);
			}

			// Remove leading delimiters
			while (B.length() > 0 && B.at(0) == delimiter) {
				B.erase(B.begin());
			}

			return A + delimiter + B;
		}

	}
}
