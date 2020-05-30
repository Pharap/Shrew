#pragma once

// For std::end
#include <string>

// For std::remove_const_t, std::remove_reference_t
#include <type_traits>

#include "match_result.h"

namespace shrew
{
	/// Represents a sequence of sub-rules.
	template<typename ... Expressions>
	struct sequence;

	template<typename Expression>
	struct sequence<Expression>
	{
		template<typename Iterator>
		static match_result<Iterator> match(Iterator && begin, Iterator && end)
		{
			return Expression::match(begin, end);
		}
	};

	template<typename Expression, typename ... Expressions>
	struct sequence<Expression, Expressions...>
	{
		template<typename Iterator>
		static match_result<Iterator> match(Iterator && begin, Iterator && end)
		{
			const auto result = Expression::match(begin, end);

			if(!result.success())
				return make_failed_match(begin, end);

			const auto remaining = sequence<Expressions...>::match<Iterator>(std::end(result), end);

			return
				remaining.success() ?
				make_successful_match<Iterator>(begin, std::end(remaining)) :
				make_failed_match(begin, end);
		}
	};

	/// A convinience function for creating a `sequence`.
	/// Infers the resulting template parameters and removes all `const` and reference qualifiers.
	template<typename ... Expressions>
	constexpr auto make_sequence(Expressions && ...) ->
		sequence<std::remove_const_t<std::remove_reference_t<Expressions>>...>
	{
		return {};
	}
}