#pragma once

#include "alternation.h"

#include "details/remove_duplicates_helper.h"

namespace shrew
{
	/// Removes any duplicate types in a variadic template.
	template<typename Type>
	using remove_duplicates_of_type = details::remove_duplicates_of_type<Type>;


	/// Removes any duplicates of a set of types used in an `alternation`.
	template<typename ... Types>
	using remove_duplicates_of_alternation = details::remove_duplicates_of_type<alternation<Types...>>;
	
	/// Removes any duplicate types in the specified `alternation`.
	template<typename ... Types>
	constexpr auto remove_duplicates_of(alternation<Types...> &&) ->
		remove_duplicates_of_alternation<Types...>
	{
		return {};
	}
}