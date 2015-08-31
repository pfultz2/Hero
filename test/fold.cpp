#include <hero/fold.h>
#include <fit/match.h>
#include <tick/integral_constant.h>
#include "test.h"

PROVE_CASE()
{
    auto t = hero::make_tuple(12345, 'x', 678910, 3.36);
    int result = hero::fold(t, fit::match(
        [](int state, int x) { return state + x; },
        fit::lazy(fit::identity)(fit::_1)
    ), 0);
    PROVE_CHECK(result == 12345+678910);
}

PROVE_CASE()
{
    auto t = hero::make_tuple(12345, 'x', 678910, 3.36);
    int result = hero::fold(t, fit::match(
        [](int state, int x) { return state + x; },
        fit::lazy(fit::identity)(fit::_1)
    ));
    PROVE_CHECK(result == 12345+678910);
}

PROVE_CASE()
{
    auto t = hero::make_tuple(12345, 'x', 678910, 3.36);
    int result = t | hero::fold(fit::match(
        [](int state, int x) { return state + x; },
        fit::lazy(fit::identity)(fit::_1)
    ), 0);
    PROVE_CHECK(result == 12345+678910);
}

PROVE_CASE()
{
    auto t = hero::make_tuple(12345, 'x', 678910, 3.36);
    int result = t | hero::fold(fit::match(
        [](int state, int x) { return state + x; },
        fit::lazy(fit::identity)(fit::_1)
    ));
    PROVE_CHECK(result == 12345+678910);
}

PROVE_CASE()
{
    auto t = hero::make_tuple(1);
    int n = hero::fold(t, fit::_1 + 1, tick::integral_constant<int, 0>());
    PROVE_CHECK(n == 1);
}

PROVE_CASE()
{
    auto t = hero::make_tuple(1, 2);
    int n = hero::fold(t, fit::_1 + 1, tick::integral_constant<int, 0>());
    PROVE_CHECK(n == 2);
}

PROVE_CASE()
{
    auto t = hero::make_tuple('a','b','c','d','e');
    std::string s = hero::fold(t, fit::_1 + fit::_2, std::string(""));
    PROVE_CHECK(s == std::string("abcde"));
}

