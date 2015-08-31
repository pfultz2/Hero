#include <hero/for_each.h>
#include <hero/fold.h>
#include <fit/lazy.h>
#include "test.h"

PROVE_CASE()
{
    auto t = hero::make_tuple(1, 2);
    auto r = hero::view::for_each(t, [](int i) { return fit::pack(i*i); });
    PROVE_CHECK(fit::unpack(hero::make_tuple)(r) == hero::make_tuple(1, 4));
}

PROVE_CASE()
{
    auto t = hero::make_tuple(1, 2);
    auto r = t | hero::view::for_each([](int i) { return fit::pack(i*i); });
    PROVE_CHECK(fit::unpack(hero::make_tuple)(r) == hero::make_tuple(1, 4));
}
