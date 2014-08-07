
#ifndef NEBU_TRAITS_H_
#define NEBU_TRAITS_H_

#include <memory>
#include <unordered_map>
#include <string>

namespace nebu
{
	namespace common
	{

		template<typename T>
		struct Traits
		{
			typedef std::shared_ptr<T> Ptr;
			typedef std::unordered_map<std::string, Traits<T>::Ptr> Map;
			// Reference for MakePtr: http://stackoverflow.com/a/7257307
			template<typename... Args>
			static Traits<T>::Ptr MakePtr(Args &&...args) {
				return std::make_shared<T>(std::forward<Args>(args)...);
			}
		};

	}
}

#endif
