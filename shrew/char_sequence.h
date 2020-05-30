#pragma once

#include <utility>
#include <algorithm>
#include <string>

#include "match_result.h"

namespace shrew
{
	template<typename Char, typename Traits = std::char_traits<Char>, Char ... Characters>
	struct basic_char_sequence;

	template<typename Char, typename Traits, Char Character>
	struct basic_char_sequence<Char, Traits, Character>
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
	struct basic_char_sequence<Char, Traits, Character, Characters...>
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

			if(!traits::eq(*begin, Character))
				make_failed_match(begin, end);

			const auto remaining = basic_char_sequence<Char, Traits, Characters...>::match<Iterator>(next, end);

			return
				remaining.success() ?
				make_successful_match<Iterator>(begin, std::end(remaining)) :
				make_failed_match(begin, end);
		}
	};

	template<char ... chars>
	using char_sequence = basic_char_sequence<char, std::char_traits<char>, chars...>;

	template<wchar_t ... chars>
	using wchar_sequence = basic_char_sequence<wchar_t, std::char_traits<wchar_t>, chars...>;

	template<char16_t ... chars>
	using char16_sequence = basic_char_sequence<char16_t, std::char_traits<char16_t>, chars...>;

	template<char32_t ... chars>
	using char32_sequence = basic_char_sequence<char32_t, std::char_traits<char32_t>, chars...>;
}