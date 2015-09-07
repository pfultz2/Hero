/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    algo.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HERO_GUARD_ALGO_H
#define HERO_GUARD_ALGO_H

#include <hero/fill.h>
#include <hero/detail/unpack.h>
#include <tick/requires.h>

namespace hero { namespace detail {

template<class A>
struct algo
{
    // TODO: Check type requirements for sequence
    template<class Sequence, class... Ts, TICK_REQUIRES(fit::is_unpackable<Sequence>::value)>
    constexpr auto operator()(Sequence&& s, Ts&&... xs) const FIT_RETURNS
    (
        fit::unpack(A()(fill(s), fit::forward<Ts>(xs)...))(fit::forward<Sequence>(s))
    )


    // template<class Sequence, class... Ts, TICK_REQUIRES(fit::is_unpackable<Sequence>())>
    // constexpr auto operator()(Sequence&& s, Ts&&... xs) const
    // {
    //     return fit::reveal(fit::unpack(A()(fill(s), fit::forward<Ts>(xs)...)))(fit::forward<Sequence>(s));
    // }
};

template<class A>
constexpr algo<A> make_algo(A)
{
    return {};
}

template<class A>
struct algo_action
{
    template<class Sequence, class... Ts, TICK_REQUIRES(fit::is_unpackable<Sequence>::value)>
    constexpr auto operator()(Sequence&& s, Ts&&... xs) const FIT_RETURNS
    (
        fit::unpack(A()(fit::forward<Ts>(xs)...))(fit::forward<Sequence>(s))
    )
};

template<class A>
constexpr algo_action<A> make_algo_action(A)
{
    return {};
}

}}

#endif