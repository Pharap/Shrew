#pragma once

#include <utility>
#include <algorithm>
#include <type_traits>

#include "match_result.h"

namespace shrew
{
	template<typename Expression>
	struct optional
	{
		template<typename Iterator>
		static match_result<Iterator> match(Iterator && begin, Iterator && end)
		{
			const auto result = Expression::match(begin, end);

			return result.success() ? result : make_successful_match(begin, begin);
		}
	};

	template<typename Expression>
	constexpr auto make_optional(Expression && ...) ->
		optional<std::remove_const_t<std::remove_reference_t<Expression>>>
	{
		return {};
	}
}