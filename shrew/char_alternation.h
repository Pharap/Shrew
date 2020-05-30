#pragma once

#include <utility>
#include <algorithm>
#include <string>

#include "match_result.h"

namespace shrew
{
	template<typename Char, typename Traits = std::char_traits<Char>, Char ... Characters>
	struct basic_char_alternation;

	template<typename Char, typename Traits, Char Character>
	struct basic_char_alternation<Char, Traits, Character>
	{
		using char_type = Char;
		using traits = Traits;

		template<typename Iterator>
		static auto match(Iterator && begin, Iterator && end) -> match_result<Iterator>
		{
			if(begin == end)
				return make_failed_match(begin, end);

			auto next = begin;
			++next;

			return traits::eq(*begin, Character) ?
				make_successful_match<Iterator>(begin, next) :
				make_failed_match(begin, end);
		}
	};

	template<typename Char, typename Traits, Char Character, Char ... Characters>
	struct basic_char_alternation<Char, Traits, Character, Characters...>
	{
		using char_type = Char;
		using traits = Traits;

		template<typename Iterator>
		static auto match(Iterator && begin, Iterator && end) -> match_result<Iterator>
		{
			if(begin == end)
				return make_failed_match(begin, end);

			auto next = begin;
			++next;

			if(traits::eq(*begin, Character))
				make_successful_match<Iterator>(begin, next);

			const auto remaining = basic_char_alternation<Char, Traits, Characters...>::match<Iterator>(begin, end);

			return
				remaining.success() ?
				remaining :
				make_failed_match(begin, end);
		}
	};

	template<char ... chars>
	using char_alternation = basic_char_alternation<char, std::char_traits<char>, chars...>;

	template<wchar_t ... chars>
	using wchar_alternation = basic_char_alternation<wchar_t, std::char_traits<wchar_t>, chars...>;

	template<char16_t ... chars>
	using char16_alternation = basic_char_alternation<char16_t, std::char_traits<char16_t>, chars...>;

	template<char32_t ... chars>
	using char32_alternation = basic_char_alternation<char32_t, std::char_traits<char32_t>, chars...>;
}