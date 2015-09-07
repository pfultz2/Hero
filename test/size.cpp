#include <hero/size.h>
#include <hero/tuple.h>
#include "test.h"

PROVE_CASE()
{
    PROVE_CHECK(hero::size(hero::make_tuple()) == 0);
    PROVE_CHECK(hero::size(fit::pack()) == 0);

    PROVE_CHECK(hero::size(hero::make_tuple(1)) == 1);
    PROVE_CHECK(hero::size(fit::pack(1)) == 1);

    PROVE_CHECK(hero::size(hero::make_tuple(1, 2)) == 2);
    PROVE_CHECK(hero::size(fit::pack(1, 2)) == 2);

    PROVE_CHECK(hero::size(hero::make_tuple(1, 2, 3)) == 3);
    PROVE_CHECK(hero::size(fit::pack(1, 2, 3)) == 3);

    PROVE_STATIC_CHECK(hero::size(hero::make_tuple()) == 0);
    PROVE_STATIC_CHECK(hero::size(fit::pack()) == 0);

    PROVE_STATIC_CHECK(hero::size(hero::make_tuple(1)) == 1);
    PROVE_STATIC_CHECK(hero::size(fit::pack(1)) == 1);

    PROVE_STATIC_CHECK(hero::size(hero::make_tuple(1, 2)) == 2);
    PROVE_STATIC_CHECK(hero::size(fit::pack(1, 2)) == 2);

    PROVE_STATIC_CHECK(hero::size(hero::make_tuple(1, 2, 3)) == 3);
    PROVE_STATIC_CHECK(hero::size(fit::pack(1, 2, 3)) == 3);
}
