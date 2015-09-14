/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    view.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HERO_GUARD_VIEW_H
#define HERO_GUARD_VIEW_H

#include <hero/detail/unpack.h>
// #include <fit/rotate.h>
#include <fit/construct.h>
#include <tick/requires.h>

namespace hero { namespace detail {

template<class A>
struct invoke_algo
{
    template<class Sequence, class Pack, class F>
    constexpr auto operator()(Sequence&& s, Pack&& p, F&& f) const FIT_RETURNS
    (
        fit::unpack(
            fit::pack_join(fit::pack(f), p)(A())
        )(fit::forward<Sequence>(s))
    )
};

template<class A>
struct view : A
{
    FIT_INHERIT_CONSTRUCTOR(view, A)
    struct hero_unpack_sequence
    {
        template<class F, class S>
        constexpr static auto apply(F&& f, S&& s) FIT_RETURNS
        (
            s(f)
        );
    };
};

template<class A>
struct make_view
{
    template<class Sequence, class... Ts, 
        TICK_REQUIRES(fit::is_unpackable<Sequence>::value && fit::is_callable<A, decltype(fit::always()), Ts...>::value)>
    constexpr auto operator()(Sequence&& s, Ts&&... xs) const FIT_RETURNS
    (
        fit::construct<view>()(
            fit::capture(fit::forward<Sequence>(s), fit::pack(fit::forward<Ts>(xs)...))
            (invoke_algo<A>())
        )
    )
};


}}

#endif