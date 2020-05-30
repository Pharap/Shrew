#pragma once

#include <utility>
#include <algorithm>
#include <type_traits>

namespace shrew
{
	template<typename Iterator>
	struct basic_match_result
	{
	public:
		using iterator = std::remove_const_t<std::remove_reference_t<Iterator>>;

	private:
		bool success_value;
		iterator begin_iterator;
		iterator end_iterator;

	public:
		template<typename Iterator>
		constexpr basic_match_result(bool success_value, Iterator && begin_iterator, Iterator && end_iterator) :
			success_value(success_value),
			begin_iterator(std::forward<Iterator>(begin_iterator)),
			end_iterator(std::forward<Iterator>(end_iterator))
		{
		}

		constexpr bool success() const
		{
			return this->success_value;
		}

		constexpr iterator begin() const
		{
			return this->begin_iterator;
		}

		constexpr iterator end() const
		{
			return this->end_iterator;
		}
	};

	template<typename Iterator>
	using match_result = basic_match_result<std::remove_const_t<std::remove_reference_t<Iterator>>>;
	
	template<typename Iterator>
	constexpr auto make_successful_match(Iterator && begin_iterator, Iterator && end_iterator) ->
		match_result<Iterator>
	{
		return match_result<Iterator>(true, std::forward<Iterator>(begin_iterator), std::forward<Iterator>(end_iterator));
	}

	template<typename Iterator>
	constexpr auto make_failed_match(Iterator && begin_iterator, Iterator && end_iterator) ->
		match_result<Iterator>
	{
		return match_result<Iterator>(false, std::forward<Iterator>(begin_iterator), std::forward<Iterator>(end_iterator));
	}
}