/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    empty.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HERO_GUARD_EMPTY_H
#define HERO_GUARD_EMPTY_H

#include <hero/detail/unpack.h>
#include <tick/integral_constant.h>
#include <tick/requires.h>
#include <fit/pipable.h>
#include <fit/function.h>

namespace hero { namespace detail {

struct is_empty
{
    template<class... Ts>
    constexpr tick::integral_constant<bool, false> operator()(Ts&&...) const
    {
        return {};
    }

    template<class... Ts>
    constexpr tick::integral_constant<bool, true> operator()() const
    {
        return {};
    }
};

struct empty_f
{
    template<class Sequence, TICK_REQUIRES(fit::is_unpackable<Sequence>::value)>
    constexpr auto operator()(Sequence&& s) const FIT_RETURNS(fit::unpack(is_empty())(s))
};

}

FIT_STATIC_FUNCTION(empty) = fit::pipable(detail::empty_f());

}

#endif
