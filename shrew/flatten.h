#pragma once

#include "alternation.h"
#include "sequence.h"

#include "details/flatten_helper.h"

namespace shrew
{
	/// Flattens any `alternation`s in `Rules`.
	template<typename ... Rules>
	using flat_alternation = details::flatten_type<alternation, Rules...>;

	/// Flattens any `sequence`s in `Rules`.
	template<typename ... Rules>
	using flat_sequence = details::flatten_type<sequence, Rules...>;

	/// Flattens the rule to the extent possible
	template<typename Rule>
	constexpr Rule flatten(Rule &&)
	{
		return {};
	}

	template<typename ... Rules>
	constexpr auto flatten(alternation<Rules ...> &&) ->
		flat_alternation<Rules...>
	{
		return {};
	}
	
	template<typename ... Rules>
	constexpr auto flatten(sequence<Rules ...> &&) ->
		flat_sequence<Rules...>
	{
		return {};
	}
}