
#ifndef NEBU_EXCEPTIONS_H_
#define NEBU_EXCEPTIONS_H_

#include <string>

#define WRAP_NEBU_SERVER_EXCEPTION(ex, exType) \
	NebuServerException("Caught underlying exception of type " exType ":\n" + ex.what())

namespace nebu
{
	namespace common
	{

		class NebuException
		{
		public:
			explicit NebuException(const std::string &msg) : msg(msg) { };
			virtual ~NebuException() { };
			virtual std::string what() const { return msg; };

		protected:
			std::string msg;
		};

		class IllegalArgumentException : public NebuException
		{
		public:
			explicit IllegalArgumentException(const std::string &msg) :
				NebuException(msg) { };
			virtual ~IllegalArgumentException() { };
			using NebuException::what;
		};

		class XMLParseException : public NebuException
		{
		public:
			explicit XMLParseException(const std::string &msg) : NebuException(msg) { };
			virtual ~XMLParseException() { };
			using NebuException::what;
		};

		class NebuServerException : public NebuException
		{
		public:
			explicit NebuServerException(const std::string &msg) : NebuException(msg) { };
			virtual ~NebuServerException() { };
			using NebuException::what;
		};

	}
}

#endif

