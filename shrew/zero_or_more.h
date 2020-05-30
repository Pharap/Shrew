#pragma once

#include <utility>
#include <algorithm>

#include "match_result.h"

namespace shrew
{
	template<typename Expression>
	struct zero_or_more
	{
		template<typename Iterator>
		static match_result<Iterator> match(Iterator && begin, Iterator && end)
		{
			auto current_end = begin;

			while(true)
			{
				const auto current_result = Expression::match<Iterator>(current_end, end);

				if(!current_result.success())
					break;

				current_end = current_result.end();
			}

			return make_successful_match<Iterator>(begin, current_end);
		}
	};

	template<typename Expression>
	constexpr auto make_zero_or_more(Expression && ...) ->
		zero_or_more<std::remove_const_t<std::remove_reference_t<Expression>>>
	{
		return {};
	}
}