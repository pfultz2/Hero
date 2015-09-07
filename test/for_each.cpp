#include <hero/for_each.h>
#include <hero/fold.h>
#include <fit/lazy.h>
#include <fit/match.h>
#include <hero/size.h>
#include <hero/empty.h>
#include <hero/transform.h>
#include "test.h"

PROVE_CASE()
{
    auto t = hero::make_tuple(1, 2);
    auto r = hero::view::for_each(t, [](int i) { return fit::pack(i*i); });
    PROVE_CHECK(hero::as_tuple(r) == hero::make_tuple(1, 4));
}

PROVE_CASE()
{
    auto t = hero::make_tuple(1, 2);
    auto r = t | hero::view::for_each([](int i) { return fit::pack(i*i); });
    PROVE_CHECK(hero::as_tuple(r) == hero::make_tuple(1, 4));
}

PROVE_CASE()
{
    auto t = hero::make_tuple(1, 2);
    auto r = hero::view::for_each(t, [](int i) { return hero::yield(i*i); });
    PROVE_CHECK(hero::as_tuple(r) == hero::make_tuple(1, 4));
}

PROVE_CASE()
{
    auto t = hero::make_tuple(1, 2);
    auto r = t | hero::view::for_each([](int i) { return hero::yield(i*i); });
    PROVE_CHECK(hero::as_tuple(r) == hero::make_tuple(1, 4));
}

PROVE_CASE()
{
    auto t = hero::make_tuple(1, 2);
    auto r = hero::view::for_each(t, [](int i) { return hero::yield(i*1.0); });
    PROVE_CHECK(hero::as_tuple(r) == hero::make_tuple(1.0, 2.0));
}

PROVE_CASE()
{
    auto t = hero::make_tuple(1, 2);
    auto r = t | hero::view::for_each([](int i) { return hero::yield(i*1.0); });
    PROVE_CHECK(hero::as_tuple(r) == hero::make_tuple(1.0, 2.0));
}

PROVE_CASE()
{
    PROVE_CHECK(hero::size(hero::yield(1)) == 1);
    PROVE_STATIC_CHECK(hero::size(hero::yield(1)) == 1);
}

PROVE_CASE()
{
    PROVE_CHECK(hero::size(hero::yield_if(std::true_type())(1)) == 1);
    PROVE_CHECK(hero::size(hero::yield_if(std::false_type())(1)) == 0);

    PROVE_STRINGIZE(hero::size(hero::yield_if(tick::true_type())(1)) == 1);
    PROVE_STRINGIZE(hero::size(hero::yield_if(tick::false_type())(1)) == 0);
}

PROVE_CASE()
{
    auto t = hero::make_tuple(1, 2, 'x', 3);
    auto r = t | hero::view::for_each(fit::match(
        [](int i) { return hero::yield(i); },
        [](char) { return hero::yield(); }
    ));
    PROVE_CHECK(hero::as_tuple(r) == hero::make_tuple(1, 2, 3));
}

PROVE_CASE()
{
    auto t = hero::make_tuple(1, 2, 'x', 3);
    auto r = hero::view::for_each(t, fit::match(
        [](int i) { return hero::yield(i); },
        [](char) { return hero::yield(); }
    ));
    PROVE_CHECK(hero::as_tuple(r) == hero::make_tuple(1, 2, 3));
}

struct is_integer
{
    template<class T>
    constexpr auto operator()(T x) const FIT_RETURNS
    (
        hero::yield_if(std::is_same<T, int>())(x)
    )
};

PROVE_CASE()
{
    auto t = hero::make_tuple(1, 2, 'x', 3);
    auto r = t | hero::view::for_each(is_integer());
    PROVE_CHECK(hero::as_tuple(r) == hero::make_tuple(1, 2, 3));
}

