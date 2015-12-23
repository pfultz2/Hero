/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    pair.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HERO_GUARD_PAIR_H
#define HERO_GUARD_PAIR_H

#include <hero/tuple.h>
#include <hero/detail/visit_overloads.h>

namespace hero {

template<class First, class Second>
struct pair
: tuple<First, Second>
{
    typedef tuple<First, Second> base;
    FIT_INHERIT_CONSTRUCTOR(pair, base)
};

FIT_STATIC_FUNCTION(make_pair) = fit::by(fit::decay, fit::construct<pair>());

FIT_STATIC_FUNCTION(as_pair) = fit::unpack(make_pair);


#define HERO_DETAIL_PAIR_ACCESS(ref, move, name, index) \
template<class First, class Second> \
constexpr auto name(pair<First, Second> ref x) \
{ \
    return tuple<First, Second>::template get_by_key<std::integral_constant<int, index>>(move(x)); \
}

#define HERO_DETAIL_PAIR_FIRST(ref, move) HERO_DETAIL_PAIR_ACCESS(ref, move, first, 0)
HERO_UNARY_PERFECT_FOREACH(HERO_DETAIL_PAIR_FIRST)
#define HERO_DETAIL_PAIR_SECOND(ref, move) HERO_DETAIL_PAIR_ACCESS(ref, move, second, 1)
HERO_UNARY_PERFECT_FOREACH(HERO_DETAIL_PAIR_SECOND)

}

#endif