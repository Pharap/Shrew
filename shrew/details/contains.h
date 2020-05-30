#pragma once

#include <type_traits>

namespace shrew
{
	namespace details
	{
		// Determines whether `Types` contains `Type`
		template<typename Type, typename ... Types>
		struct contains;

		template<typename Type>
		struct contains<Type> :
			std::integral_constant<bool, false>
		{
		};

		template<typename Type, typename Rule, typename ... Remaining>
		struct contains<Type, Rule, Remaining...> :
			std::integral_constant<bool, std::is_same<Type, Rule>::value || contains<Type, Remaining...>::value>
		{
		};
	}
}