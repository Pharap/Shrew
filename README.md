# Shrew

## Intro

This library is, roughly speaking, a regular expression library where the regular expressions are defined at compile time using template wizardry.

Aside from character types, the regular expressions in this library can be used on sequences of types other than characters.  
However, there's no support for any other types provided by default.

## Operators

`shrew::operators` contains various operator overloads designed to make defining expressions easier.  
In order to use the operators, you must bring the `shrew::operators` namespace into scope with `using shrew::operators;`.  
Note that doing so may cause the operators to interfere with other operator definitions.  
(It would be possible to use SFINAE to limit which types participate in overload resolution with the operators,  
but I have not gone to that trouble as this library is meant more as a proof of concept than as a robust programming tool.)  

The operators are as thus:
* `-` - unary minus - Wraps the expression following the operator in a `shrew::optional`, removing any `const` or reference qualifiers.
* `+` - unary plus - Wraps the expression following the operator in a `shrew::one_or_more`, removing any `const` or reference qualifiers. 
* `*` - indirection - Wraps the expression following the operator in a `shrew::zero_or_more`, removing any `const` or reference qualifiers. 
* `/` - division - Wraps the expressions either side of the operator in a `shrew::alternation`, removing any `const` or reference qualifiers, and if either expression is a `shrew::alternation`, lifts the `alternation`'s contents to avoid nesting - i.e. `decltype(shrew::alternation<char>{} / 0)` is `shrew::alternation<char, int>` rather than `shrew::alternation<shrew::alternation<char>, int>`.
* `>>` - bitwise right shift - Wraps the expressions either side of the operator in a `shrew::sequence`, removing any `const` or reference qualifiers, and if either expression is a `shrew::sequence`, lifts the `sequence`'s contents to avoid nesting - i.e. `decltype(shrew::sequence<char>{} >> 0)` is `shrew::sequence<char, int>` rather than `shrew::sequence<shrew::sequence<char>, int>`.

Notes:
* `/` was chosen over `|` to emphasise that alternation is ordered, as it is in packrat parsing.
* `>>` was chosen over `,` because the comma operator is only interpreted as an operator in certain contexts and would thus require more effort to use.
* Similarly, all operators chosen have assignment operator equivalents, should the library be expanded to include rules that can be constructed at runtime.

## Examples

Using operators to define character matching rules:
```cpp
namespace rules
{
    using namespace shrew;
    using namespace shrew::operators;

    constexpr auto lowercase = char_range<'a', 'z'>();
    constexpr auto uppercase = char_range<'A', 'Z'>();
    constexpr auto underscore = char_range<'_'>();
    constexpr auto letter = (lowercase / uppercase);

    constexpr auto decimal_digit = char_range<'0', '9'>();
    constexpr auto decimal_integer = +decimal_digit;

    constexpr auto alphanumeric = (letter / decimal_digits);

    constexpr auto lowercase_hex = char_range<'a', 'f'>();
    constexpr auto uppercase_hex = char_range<'A', 'F'>();
    constexpr auto hexadecimal_digit = (lowercase_hex / uppercase_hex / decimal_digit);
    constexpr auto hexadecimal_integer = +hexadecimal_digits;    

    constexpr auto whitespace_character = char_alternation<' ', '\n'>();
    constexpr auto whitespace = +whitespace_character;

    // Equivalent to regex "[a-zA-Z_][a-zA-Z0-9_]*"
    constexpr auto identifier = ((letter / underscore) >> *(alphanumeric / underscore));

    constexpr auto operator_symbol = char_alternation<'+', '-', '/', '*', '%'>();
}
```
