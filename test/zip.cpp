#include <hero/zip.h>
#include <hero/fold.h>
#include <fit/placeholders.hpp>
#include "test.h"

PROVE_CASE()
{
    auto x = hero::make_tuple(1, 2);
    auto y = hero::make_tuple(3, 4);
    auto zip_product = hero::zip_with(x, y, fit::_ * fit::_);
    int r = hero::fold(zip_product, fit::_ + fit::_);
    PROVE_CHECK(r == (1*3) + (2*4));
}

PROVE_CASE()
{
    auto x = hero::make_tuple(1, 2);
    auto y = hero::make_tuple(3, 4);
    auto zip_product = x | hero::zip_with(y, fit::_ * fit::_);
    int r = hero::fold(zip_product, fit::_ + fit::_);
    PROVE_CHECK(r == (1*3) + (2*4));
}

PROVE_CASE()
{
    auto x = hero::make_tuple(1, 2);
    auto y = hero::make_tuple(3, 4);
    auto zip_product = hero::view::zip_with(x, y, fit::_ * fit::_);
    int r = hero::fold(zip_product, fit::_ + fit::_);
    PROVE_CHECK(r == (1*3) + (2*4));
}

PROVE_CASE()
{
    auto x = hero::make_tuple(1, 2);
    auto y = hero::make_tuple(3, 4);
    auto zip_product = x | hero::view::zip_with(y, fit::_ * fit::_);
    int r = hero::fold(zip_product, fit::_ + fit::_);
    PROVE_CHECK(r == (1*3) + (2*4));
}

PROVE_CASE()
{
    PROVE_STATIC_CHECK(
        hero::fold(
            hero::zip_with(hero::make_tuple(1, 2), hero::make_tuple(3, 4), fit::_ * fit::_), 
            fit::_ + fit::_) 
        == (1*3) + (2*4));
}

PROVE_CASE()
{
    PROVE_STATIC_CHECK(
        hero::fold(
            hero::make_tuple(1, 2) | hero::zip_with(hero::make_tuple(3, 4), fit::_ * fit::_), 
            fit::_ + fit::_) 
        == (1*3) + (2*4));
}

PROVE_CASE()
{
    PROVE_STATIC_CHECK(
        hero::fold(
            hero::view::zip_with(hero::make_tuple(1, 2), hero::make_tuple(3, 4), fit::_ * fit::_), 
            fit::_ + fit::_) 
        == (1*3) + (2*4));
}

PROVE_CASE()
{
    PROVE_STATIC_CHECK(
        hero::fold(
            hero::make_tuple(1, 2) | hero::view::zip_with(hero::make_tuple(3, 4), fit::_ * fit::_), 
            fit::_ + fit::_) 
        == (1*3) + (2*4));
}
