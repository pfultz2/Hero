#include <hero/pair.h>
#include "test.h"

PROVE_CASE()
{
    auto t = hero::make_pair(1, 2);
    PROVE_CHECK(hero::first(t) == 1);
    PROVE_CHECK(hero::second(t) == 2);

    PROVE_STATIC_CHECK(hero::first(hero::make_pair(1, 2)) == 1);
    PROVE_STATIC_CHECK(hero::second(hero::make_pair(1, 2)) == 2);
}

PROVE_CASE()
{
    auto t1 = hero::make_pair(1, 2);
    auto t2 = hero::make_pair(1, 2);
    PROVE_CHECK(t1 == t2);
    PROVE_CHECK(!(t1 < t2));
    PROVE_CHECK(!(t1 > t2));
    PROVE_CHECK(t1 <= t2);
    PROVE_CHECK(t1 >= t2);
}

PROVE_CASE()
{
    PROVE_STATIC_CHECK(hero::make_pair(1, 2) == hero::make_pair(1, 2));
    PROVE_STATIC_CHECK(!(hero::make_pair(1, 2) < hero::make_pair(1, 2)));
    PROVE_STATIC_CHECK(!(hero::make_pair(1, 2) > hero::make_pair(1, 2)));
    PROVE_STATIC_CHECK(hero::make_pair(1, 2) <= hero::make_pair(1, 2));
    PROVE_STATIC_CHECK(hero::make_pair(1, 2) >= hero::make_pair(1, 2));
}
