/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    push_front.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HERO_GUARD_PUSH_FRONT_H
#define HERO_GUARD_PUSH_FRONT_H

#include <hero/detail/algo.h>
#include <hero/detail/view.h>
#include <fit/pipable.hpp>

namespace hero { namespace detail {

struct push_front_a
{
    template<class Filler, class T>
    constexpr auto operator()(Filler&& f, T&& x) const FIT_RETURNS
    (
        fit::capture_decay(fit::forward<T>(x))(f)
    )
};

}

FIT_STATIC_FUNCTION(push_front) = fit::pipable(detail::algo_copy<detail::push_front_a>());

namespace view {

FIT_STATIC_FUNCTION(push_front) = fit::pipable(detail::make_view<detail::push_front_a>());

}

}

#endif
