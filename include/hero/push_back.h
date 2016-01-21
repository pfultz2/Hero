/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    push_back.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HERO_GUARD_PUSH_BACK_H
#define HERO_GUARD_PUSH_BACK_H

#include <hero/detail/algo.h>
#include <hero/detail/view.h>
#include <fit/pipable.hpp>
#include <fit/rotate.hpp>

namespace hero { namespace detail {

struct push_back_a
{
    template<class Filler, class T>
    constexpr auto operator()(Filler&& f, T&& x) const FIT_RETURNS
    (
        fit::capture_decay(fit::forward<T>(x))(fit::rotate(f))
    )
};

}

FIT_STATIC_FUNCTION(push_back) = fit::pipable(detail::algo_copy<detail::push_back_a>());

namespace view {

FIT_STATIC_FUNCTION(push_back) = fit::pipable(detail::make_view<detail::push_back_a>());

}

}

#endif
