#pragma once

namespace shrew
{
	namespace details
	{
		template<template <typename...> typename Template, typename Result, typename ... Remaining>
		struct flatten_helper;

		template<template <typename...> typename Template, typename Result, typename ... Remaining>
		struct flatten_helper_template_step;

		template<template <typename...> typename Template, typename Result, typename ... Remaining>
		struct flatten_helper_shift_step;

		// Forward to template step
		template<template <typename...> typename Template, typename Result, typename ... Remaining >
		struct flatten_helper :
			flatten_helper_template_step<Template, Result, Remaining...>
		{
		};

		// If no excess remains, a result has been found.
		template<template <typename...> typename Template, typename ... Results>
		struct flatten_helper<Template, Template<Results...>>
		{
			using type = Template<Results...>;
		};

		// If no excess remains, defer to base case.
		template<template <typename...> typename Template, typename ... Results>
		struct flatten_helper_shift_step<Template, Template<Results...>> :
			flatten_helper<Template, Template<Results...>>
		{
		};

		// Shifts if possible.
		template<template <typename...> typename Template, typename ... Results, typename Rule, typename ... Remaining>
		struct flatten_helper_shift_step<Template, Template<Results...>, Rule, Remaining...> :
			flatten_helper<Template, Template<Results..., Rule>, Remaining...>
		{
		};

		// No template matched, so try to shift.
		template<template <typename...> typename Template, typename Result, typename ... Remaining >
		struct flatten_helper_template_step :
			flatten_helper_shift_step<Template, Result, Remaining...>
		{
		};

		// Matches template, performs flattening.
		template<template <typename...> typename Template, typename ... Results, typename ... InnerExpressions, typename ... Remaining >
		struct flatten_helper_template_step<Template, Template<Results...>, Template<InnerExpressions...>, Remaining ...> :
			flatten_helper_template_step<Template, Template<Results...>, InnerExpressions..., Remaining...>
		{
		};

		// A helper alias to simplify external definitions.
		template<template <typename...> typename Template, typename Result, typename ... Remaining>
		using flatten_helper_type = typename flatten_helper<Template, Result, Remaining...>::type;

		// A helper alias to simplify external definitions.
		template<template <typename...> typename Template, typename ... Remaining>
		using flatten_type = flatten_helper_type<Template, Template<>, Remaining...>;
	}
}