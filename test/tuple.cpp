#include <hero/tuple.h>
#include "test.h"

PROVE_CASE()
{
    auto t1 = hero::make_tuple(1, 2, 3);
    auto t2 = hero::make_tuple(1, 2, 3);
    PROVE_CHECK(t1 == t2);
}

PROVE_CASE()
{
    auto t = hero::make_tuple();
    PROVE_CHECK(t.size() == 0);
    PROVE_STATIC_CHECK(t.size() == 0);

    PROVE_CHECK(t.empty());
    PROVE_STATIC_CHECK(t.empty());
}

PROVE_CASE()
{
    auto t = hero::make_tuple(hero::make_tuple(hero::make_tuple()), hero::make_tuple(hero::make_tuple()), hero::make_tuple(hero::make_tuple()));
    PROVE_CHECK(t.size() == 3);
    PROVE_STATIC_CHECK(t.size() == 3);

    PROVE_CHECK(not t.empty());
    PROVE_STATIC_CHECK(not t.empty());

    PROVE_CHECK(t[std::integral_constant<int, 0>()].size() == 1);
    PROVE_CHECK(t[std::integral_constant<int, 0>()][std::integral_constant<int, 0>()].empty());

    PROVE_CHECK(t[std::integral_constant<int, 1>()].size() == 1);
    PROVE_CHECK(t[std::integral_constant<int, 1>()][std::integral_constant<int, 0>()].empty());

    PROVE_CHECK(t[std::integral_constant<int, 2>()].size() == 1);
    PROVE_CHECK(t[std::integral_constant<int, 2>()][std::integral_constant<int, 0>()].empty());

    PROVE_STATIC_CHECK(t[std::integral_constant<int, 0>()].size() == 1);
    PROVE_STATIC_CHECK(t[std::integral_constant<int, 0>()][std::integral_constant<int, 0>()].empty());

    PROVE_STATIC_CHECK(t[std::integral_constant<int, 1>()].size() == 1);
    PROVE_STATIC_CHECK(t[std::integral_constant<int, 1>()][std::integral_constant<int, 0>()].empty());

    PROVE_STATIC_CHECK(t[std::integral_constant<int, 2>()].size() == 1);
    PROVE_STATIC_CHECK(t[std::integral_constant<int, 2>()][std::integral_constant<int, 0>()].empty());
}


PROVE_CASE()
{
    auto t = hero::make_tuple(1, 2, 3);
    PROVE_CHECK(t.size() == 3);
    PROVE_STATIC_CHECK(t.size() == 3);

    PROVE_CHECK(not t.empty());
    PROVE_STATIC_CHECK(not t.empty());

    PROVE_CHECK(t[std::integral_constant<int, 0>()] == 1);
    PROVE_CHECK(t[std::integral_constant<int, 1>()] == 2);
    PROVE_CHECK(t[std::integral_constant<int, 2>()] == 3);

    PROVE_CHECK(t[std::integral_constant<long, 0>()] == 1);
    PROVE_CHECK(t[std::integral_constant<long, 1>()] == 2);
    PROVE_CHECK(t[std::integral_constant<long, 2>()] == 3);

    PROVE_CHECK(t[tick::integral_constant<int, 0>()] == 1);
    PROVE_CHECK(t[tick::integral_constant<int, 1>()] == 2);
    PROVE_CHECK(t[tick::integral_constant<int, 2>()] == 3);

    PROVE_CHECK(t[tick::integral_constant<long, 0>()] == 1);
    PROVE_CHECK(t[tick::integral_constant<long, 1>()] == 2);
    PROVE_CHECK(t[tick::integral_constant<long, 2>()] == 3);
}

