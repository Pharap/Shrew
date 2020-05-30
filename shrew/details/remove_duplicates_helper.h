#pragma once

#include <type_traits>

#include "contains.h"

namespace shrew
{
	namespace details
	{
		// Removes all duplicates in `Types`, returning an instantiation of `Template`.
		// `Result` is an instantiation of `Template` used to accumulate the result types.
		template<template <typename...> typename Template, typename Result, typename ... Types>
		struct remove_duplicates_helper;

		template<template <typename...> typename Template, typename ... Results>
		struct remove_duplicates_helper<Template, Template<Results...>>
		{
			using type = Template<Results...>;
		};

		template<template <typename...> typename Template, typename ... Results, typename Rule, typename ... Remaining>
		struct remove_duplicates_helper<Template, Template<Results...>, typename Rule, Remaining...> :
			std::conditional_t
			<
			contains<Rule, Results...>::value,
			remove_duplicates_helper<Template, Template<Results...>, Remaining...>,
			remove_duplicates_helper<Template, Template<Results..., Rule>, Remaining...>
			>
		{
		};

		template<template <typename...> typename Template, typename Result, typename ... Remaining>
		using remove_duplicates_helper_type = typename remove_duplicates_helper<Template, Result, Remaining...>::type;

		template<template <typename...> typename Template, typename ... Remaining>
		using remove_duplicates_type = typename remove_duplicates_helper<Template, Template<>, Remaining...>::type;

		// A helper used to infer parameters for `remove_duplicates_helper`.
		template<typename Type>
		struct remove_duplicates_of_helper;

		template<template <typename...> typename Template, typename ... Types>
		struct remove_duplicates_of_helper<Template<Types...>>
		{
			using type = typename remove_duplicates_helper<Template, Template<>, Types...>::type;
		};

		template<typename Type>
		using remove_duplicates_of_type = typename remove_duplicates_of_helper<Type>::type;

		template<typename Type>
		constexpr auto remove_duplicates_of(Type &&) -> remove_duplicates_of_type<Type>
		{
			return {};
		}
	}
}
