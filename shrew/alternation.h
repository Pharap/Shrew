#pragma once

// For std::remove_const_t, std::remove_reference_t
#include <type_traits>

#include "match_result.h"

namespace shrew
{
	/// Represents an alternation of sub-rules.
	template<typename ... Expressions>
	struct alternation;

	template<typename Expression>
	struct alternation<Expression>
	{
		template<typename Iterator>
		static match_result<Iterator> match(Iterator && begin, Iterator && end)
		{
			return Expression::match(begin, end);
		}
	};

	template<typename Expression, typename ... Expressions>
	struct alternation<Expression, Expressions...>
	{
		template<typename Iterator>
		static match_result<Iterator> match(Iterator && begin, Iterator && end)
		{
			const auto result = Expression::match(begin, end);

			if(result.success())
				return result;

			const auto remaining = alternation<Expressions...>::match(begin, end);

			return
				remaining.success() ?
				remaining :
				make_failed_match(begin, end);
		}
	};

	/// A convinience function for creating an `alternation`.
	/// Infers the resulting template parameters and removes all `const` and reference qualifiers.
	template<typename ... Expressions>
	constexpr auto make_alternation(Expressions && ...) ->
		alternation<std::remove_const_t<std::remove_reference_t<Expressions>>...>
	{
		return {};
	}
}
