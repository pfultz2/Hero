#include <hero/push_front.h>
#include "test.h"

PROVE_CASE()
{
    auto t = hero::make_tuple(2, 3);
    auto r = hero::push_front(t, 1);
    PROVE_CHECK(r == hero::make_tuple(1, 2, 3));
}

PROVE_CASE()
{
    auto t = hero::make_tuple(2, 3);
    auto r = t | hero::push_front(1);
    PROVE_CHECK(r == hero::make_tuple(1, 2, 3));
}

PROVE_CASE()
{
    auto t = hero::make_tuple(2, 3);
    auto r = hero::view::push_front(t, 1);
    PROVE_CHECK(hero::as_tuple(r) == hero::make_tuple(1, 2, 3));
}

PROVE_CASE()
{
    auto t = hero::make_tuple(2, 3);
    auto r = t | hero::view::push_front(1);
    PROVE_CHECK(hero::as_tuple(r) == hero::make_tuple(1, 2, 3));
}

PROVE_CASE()
{
    PROVE_STATIC_CHECK(
        hero::push_front(hero::make_tuple(2, 3), 1) 
        == hero::make_tuple(1, 2, 3)
    );
}

PROVE_CASE()
{
    PROVE_STATIC_CHECK(
        (hero::make_tuple(2, 3) | hero::push_front(1)) 
        == hero::make_tuple(1, 2, 3)
    );
}

PROVE_CASE()
{
    PROVE_STATIC_CHECK(
        hero::as_tuple(hero::view::push_front(hero::make_tuple(2, 3), 1)) 
        == hero::make_tuple(1, 2, 3)
    );
}

PROVE_CASE()
{
    PROVE_STATIC_CHECK(
        hero::as_tuple(hero::make_tuple(2, 3) | hero::view::push_front(1)) 
        == hero::make_tuple(1, 2, 3)
    );
}
