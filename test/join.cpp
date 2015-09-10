#include <hero/join.h>
#include "test.h"

PROVE_CASE()
{
    PROVE_CHECK(hero::join(hero::make_tuple(1, 2), hero::make_tuple(3, 4)) == hero::make_tuple(1, 2, 3, 4));
    PROVE_STATIC_CHECK(hero::join(hero::make_tuple(1, 2), hero::make_tuple(3, 4)) == hero::make_tuple(1, 2, 3, 4));
}

PROVE_CASE()
{
    if (hero::as_tuple(hero::view::join(hero::make_tuple(1, 2), hero::make_tuple(3, 4))) == hero::make_tuple(1, 2, 3, 4)) return;
    PROVE_CHECK(hero::as_tuple(hero::view::join(hero::make_tuple(1, 2), hero::make_tuple(3, 4))) == hero::make_tuple(1, 2, 3, 4));
    PROVE_STATIC_CHECK(hero::as_tuple(hero::view::join(hero::make_tuple(1, 2), hero::make_tuple(3, 4))) == hero::make_tuple(1, 2, 3, 4));
}
