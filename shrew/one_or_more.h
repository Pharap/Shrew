#pragma once

#include <utility>
#include <algorithm>

#include "match_result.h"

namespace shrew
{
	template<typename Expression>
	struct one_or_more
	{
		template<typename Iterator>
		static match_result<Iterator> match(Iterator && begin, Iterator && end)
		{
			const auto first_result = Expression::match<Iterator>(begin, end);

			if(!first_result.success())
				return make_failed_match(begin, end);

			auto current_end = first_result.end();

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
	constexpr auto make_one_or_more(Expression && ...) ->
		one_or_more<std::remove_const_t<std::remove_reference_t<Expression>>>
	{
		return {};
	}
}