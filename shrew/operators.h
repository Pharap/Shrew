#pragma once

#include <type_traits>

#include "shrew.h"

// Operators that can be overloaded:
//
// subscript []
// comma ,
// function call ( )
// indirection *
// address of &
// member of pointer ->
// pointer to member of pointer ->*
// comparison == |= < > <= >=
// logical ! && ||
// arithmetic + - + - * / % ~ & | ^ << >>
// inc dec ++ -- ++ --
// assignment = += -= *= /= %= &= |= ^= <<= >>=
// user literal (const char *, std::size_t), char, 

namespace shrew
{
	namespace operators
	{
		template<typename T>
		using remove_cvref = std::remove_const_t<std::remove_reference_t<T>>;

		/// A shortcut operator for applying `one_or_more`.
		template<typename Rule>
		constexpr auto operator +(Rule &&) ->
			one_or_more<remove_cvref<Rule>>
		{
			return {};
		}

		/// A shortcut operator for applying `one_or_more`.
		/// Flattens `one_or_more`s.
		template<typename Rule>
		constexpr auto operator +(one_or_more<Rule> &&) ->
			one_or_more<remove_cvref<Rule>>
		{
			return {};
		}

		/// A shortcut operator for applying `zero_or_more`.
		template<typename Rule>
		constexpr auto operator *(Rule &&) ->
			zero_or_more<remove_cvref<Rule>>
		{
			return {};
		}

		/// A shortcut operator for applying `zero_or_more`.
		/// Flattens `zero_or_more`s.
		template<typename Rule>
		constexpr auto operator *(zero_or_more<Rule> &&) ->
			zero_or_more<remove_cvref<Rule>>
		{
			return {};
		}

		/// A shortcut operator for applying `optional`.
		template<typename Rule>
		constexpr auto operator -(Rule &&) ->
			optional<remove_cvref<Rule>>
		{
			return {};
		}

		/// A shortcut operator for applying `optional`.
		/// Flattens `optional`s.
		template<typename Rule>
		constexpr auto operator -(optional<Rule> &&) ->
			optional<remove_cvref<Rule>>
		{
			return {};
		}

		/// A shortcut operator for specifying alternation of rules.
		template<typename LeftRule, typename RightRule>
		constexpr auto operator /(LeftRule &&, RightRule &&) ->
			flat_alternation<remove_cvref<LeftRule>, remove_cvref<RightRule>>
		{
			return {};
		}

		/// A shortcut operator for specifying sequencing of rules.
		template<typename LeftRule, typename RightRule>
		constexpr auto operator >> (LeftRule &&, RightRule &&) ->
			flat_sequence<remove_cvref<LeftRule>, remove_cvref<RightRule>>
		{
			return {};
		}
	}
}