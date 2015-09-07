#include <hero/push_back.h>
#include "test.h"

PROVE_CASE()
{
    auto t = hero::make_tuple(1, 2);
    auto r = hero::push_back(t, 3);
    PROVE_CHECK(r == hero::make_tuple(1, 2, 3));
}

PROVE_CASE()
{
    auto t = hero::make_tuple(1, 2);
    auto r = t | hero::push_back(3);
    PROVE_CHECK(r == hero::make_tuple(1, 2, 3));
}

PROVE_CASE()
{
    auto t = hero::make_tuple(1, 2);
    auto r = hero::view::push_back(t, 3);
    PROVE_CHECK(hero::as_tuple(r) == hero::make_tuple(1, 2, 3));
}

PROVE_CASE()
{
    auto t = hero::make_tuple(1, 2);
    auto r = t | hero::view::push_back(3);
    PROVE_CHECK(hero::as_tuple(r) == hero::make_tuple(1, 2, 3));
}

PROVE_CASE()
{
    PROVE_STATIC_CHECK(
        hero::push_back(hero::make_tuple(1, 2), 3) 
        == hero::make_tuple(1, 2, 3)
    );
}

PROVE_CASE()
{
    PROVE_STATIC_CHECK(
        (hero::make_tuple(1, 2) | hero::push_back(3)) 
        == hero::make_tuple(1, 2, 3)
    );
}

PROVE_CASE()
{
    PROVE_STATIC_CHECK(
        hero::as_tuple(hero::view::push_back(hero::make_tuple(1, 2), 3)) 
        == hero::make_tuple(1, 2, 3)
    );
}

PROVE_CASE()
{
    PROVE_STATIC_CHECK(
        hero::as_tuple(hero::make_tuple(1, 2) | hero::view::push_back(3)) 
        == hero::make_tuple(1, 2, 3)
    );
}
