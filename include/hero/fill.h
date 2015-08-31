/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    fill.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HERO_GUARD_FILL_H
#define HERO_GUARD_FILL_H

#include <hero/tuple.h>

namespace hero {

template<class, class=void>
struct fill_sequence
{
    template<class... Ts>
    constexpr auto operator()(Ts&&... xs) const 
    FIT_RETURNS(hero::tuple<Ts...>(fit::forward<Ts>(xs)...))
};

template<class... Xs>
struct fill_sequence<std::tuple<Xs...>>
{
    template<class... Ts>
    constexpr auto operator()(Ts&&... xs) const 
    FIT_RETURNS(std::tuple<Ts...>(fit::forward<Ts>(xs)...))
};

namespace detail {

struct fill_f
{
    template<class Sequence>
    constexpr fill_sequence<Sequence> 
    operator()(const Sequence&) const
    {
        return {};
    }
};

}

FIT_STATIC_FUNCTION(fill) = detail::fill_f();

}

#endif