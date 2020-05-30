#pragma once

// For std::char_traitss
#include <string>

#include "match_result.h"

namespace shrew
{
	/// Represents a range of characters.
	/// Matches a single character.
	template<typename Char, Char min, Char max = min, typename Traits = std::char_traits<Char>>
	struct basic_char_range
	{
		using char_type = Char;
		using traits = Traits;

		static_assert(traits::lt(min, max), "min must be less than max");

		template<typename Iterator>
		static match_result<Iterator> match(Iterator && begin, Iterator && end)
		{
			if(begin == end)
				return make_failed_match(begin, end);

			const char_type character = *begin;
			
			if(traits::lt(character, min) || !traits::lt(character, max))
				return make_failed_match(begin, end);

			auto next = begin;
			++next;
			
			return make_successful_match<Iterator>(begin, next);
		}
	};

	/// Represents a single character.
	/// Matches a single character.
	template<typename Char, Char character, typename Traits>
	struct basic_char_range<Char, character, character, Traits>
	{
		using char_type = Char;
		using traits = Traits;

		template<typename Iterator>
		static match_result<Iterator> match(Iterator && begin, Iterator && end)
		{
			if(begin == end)
				return make_failed_match(begin, end);

			const char_type current_character = *begin;

			if(!traits::eq(current_character, character))
				return make_failed_match(begin, end);

			auto next = begin;
			++next;

			return make_successful_match<Iterator>(begin, next);
		}
	};

	/// A convinient alias for `basic_char_range` with `char` type characters.
	template<char min, char max = min, typename Traits = std::char_traits<char>>
	using char_range = basic_char_range<char, min, max, Traits>;

	/// A convinient alias for `basic_char_range` with `wchar_t` type characters.
	template<wchar_t min, wchar_t max = min, typename Traits = std::char_traits<wchar_t>>
	using wchar_range = basic_char_range<wchar_t, min, max, Traits>;

	/// A convinient alias for `basic_char_range` with `char16_t` type characters.
	template<char16_t min, char16_t max = min, typename Traits = std::char_traits<char16_t>>
	using char16_range = basic_char_range<char16_t, min, max, Traits>;

	/// A convinient alias for `basic_char_range` with `char32_t` type characters.
	template<char32_t min, char32_t max = min, typename Traits = std::char_traits<char32_t>>
	using char32_range = basic_char_range<char32_t, min, max, Traits>;
}