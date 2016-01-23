/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    size.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HERO_GUARD_SIZE_H
#define HERO_GUARD_SIZE_H

#include <hero/detail/unpack.h>
#include <tick/integral_constant.h>
#include <tick/requires.h>
#include <fit/pipable.hpp>
#include <fit/function.hpp>

namespace hero { namespace detail {

struct get_size
{
    template<class... Ts>
    constexpr tick::integral_constant<std::size_t, sizeof...(Ts)> operator()(Ts&&...) const
    {
        return {};
    }
};

struct size_f
{
    template<class Sequence, TICK_REQUIRES(fit::is_unpackable<Sequence>::value)>
    constexpr auto operator()(Sequence&& s) const -> decltype(fit::unpack(get_size())(s))
    {
        return {};
    }
};

}

FIT_STATIC_FUNCTION(size) = fit::pipable(detail::size_f());

}

#endif
