#include <hero/empty.h>
#include <hero/tuple.h>
#include "test.h"

PROVE_CASE()
{
    PROVE_CHECK(hero::empty(hero::make_tuple()));
    PROVE_CHECK(hero::empty(fit::pack()));

    PROVE_CHECK(!hero::empty(hero::make_tuple(1)));
    PROVE_CHECK(!hero::empty(fit::pack(1)));

    PROVE_STATIC_CHECK(hero::empty(hero::make_tuple()));
    PROVE_STATIC_CHECK(hero::empty(fit::pack()));

    PROVE_STATIC_CHECK(!hero::empty(hero::make_tuple(1)));
    PROVE_STATIC_CHECK(!hero::empty(fit::pack(1)));
}

