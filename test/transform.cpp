#include <hero/transform.h>
#include <hero/fold.h>
#include <fit/lazy.h>
#include "test.h"

PROVE_CASE()
{
    auto t = hero::make_tuple(1, 2);
    auto r = hero::transform(t, [](int i) { return i*i; });
    PROVE_CHECK(r == hero::make_tuple(1, 4));
}

PROVE_CASE()
{
    auto t = hero::make_tuple(1, 2);
    auto r = t | hero::transform([](int i) { return i*i; });
    PROVE_CHECK(r == hero::make_tuple(1, 4));
}

PROVE_CASE()
{
    auto t = std::make_tuple(1, 2);
    auto r = t | hero::transform([](int i) { return i*i; });
    PROVE_CHECK(bool{r == std::make_tuple(1, 4)});
}

PROVE_CASE()
{
    auto t = hero::make_tuple(1, 2);
    auto r = hero::view::transform(t, [](int i) { return i*i; });
    static_assert(fit::is_unpackable<decltype(t)>::value, "View not packable");
    PROVE_CHECK(fit::unpack(hero::make_tuple)(r) == hero::make_tuple(1, 4));
}

PROVE_CASE()
{
    auto t = hero::make_tuple(1, 2);
    auto r = t | hero::view::transform([](int i) { return i*i; });
    PROVE_CHECK(fit::unpack(hero::make_tuple)(r) == hero::make_tuple(1, 4));
}

PROVE_CASE()
{
    PROVE_STATIC_CHECK(
        (hero::make_tuple(1, 2) | hero::transform(fit::_1 * fit::_1)) 
        == hero::make_tuple(1, 4));
}

PROVE_CASE()
{
    PROVE_STATIC_CHECK(
        (hero::transform(hero::make_tuple(1, 2), fit::_1 * fit::_1)) 
        == hero::make_tuple(1, 4));
}
