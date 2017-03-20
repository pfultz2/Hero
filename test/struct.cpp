#include <hero/struct.h>
#include <hero/fold.h>
#include "test.h"

struct foo
{
    HERO_STRUCT_TUPLE_FIELDS(
        ((int) x1)
        ((int) x2)
    );
};

PROVE_CASE()
{
    foo x{1, 2};
    PROVE_CHECK(hero::fold(x, fit::_1 + fit::_2) == 3);
}

