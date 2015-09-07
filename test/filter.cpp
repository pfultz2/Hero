#include <hero/filter.h>
#include <hero/size.h>
#include "test.h"

struct is_integer
{
    template<class T>
    constexpr auto operator()(const T&) const
    FIT_RETURNS(std::is_same<int, T>())
};

PROVE_CASE()
{
    typedef hero::detail::filter_projection<is_integer> fp;
    PROVE_CHECK(hero::size(fp()(1)) == 1);
    PROVE_CHECK(hero::size(fp()(1.0)) == 0);

    PROVE_STATIC_CHECK(hero::size(fp()(1)) == 1);
    PROVE_STATIC_CHECK(hero::size(fp()(1.0)) == 0);
}

PROVE_CASE()
{
    auto t = hero::make_tuple(1, 2, 'x', 3);
    auto r = hero::filter(t, is_integer());
    PROVE_CHECK(r == hero::make_tuple(1, 2, 3));
}

PROVE_CASE()
{
    auto t = hero::make_tuple(1, 2, 'x', 3);
    auto r = t | hero::filter(is_integer());
    PROVE_CHECK(r == hero::make_tuple(1, 2, 3));
}

PROVE_CASE()
{
    PROVE_STATIC_CHECK(
        hero::filter(hero::make_tuple(1, 2, 'x', 3), is_integer()) 
        == hero::make_tuple(1, 2, 3)
    );
}

PROVE_CASE()
{
    PROVE_STATIC_CHECK(
        (hero::make_tuple(1, 2, 'x', 3) | hero::filter(is_integer()))
        == hero::make_tuple(1, 2, 3)
    );
}

PROVE_CASE()
{
    auto t = hero::make_tuple(1, 2, 'x', 3);
    auto r = hero::view::filter(t, is_integer());
    PROVE_CHECK(hero::as_tuple(r) == hero::make_tuple(1, 2, 3));
}

PROVE_CASE()
{
    auto t = hero::make_tuple(1, 2, 'x', 3);
    auto r = t | hero::view::filter(is_integer());
    PROVE_CHECK(hero::as_tuple(r) == hero::make_tuple(1, 2, 3));
}

PROVE_CASE()
{
    PROVE_STATIC_CHECK(
        hero::as_tuple(hero::view::filter(hero::make_tuple(1, 2, 'x', 3), is_integer()))
        == hero::make_tuple(1, 2, 3)
    );
}

PROVE_CASE()
{
    PROVE_STATIC_CHECK(
        hero::as_tuple(hero::make_tuple(1, 2, 'x', 3) | hero::view::filter(is_integer()))
        == hero::make_tuple(1, 2, 3)
    );
}

