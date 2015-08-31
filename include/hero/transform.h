/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    transform.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HERO_GUARD_TRANSFORM_H
#define HERO_GUARD_TRANSFORM_H

#include <hero/detail/algo.h>
#include <hero/detail/view.h>
#include <fit/pipable.h>
#include <fit/by.h>

namespace hero { namespace detail {

struct transform_a
{
    template<class Filler, class Projection>
    constexpr auto operator()(Filler&& f, Projection&& p) const FIT_RETURNS
    (
        fit::by(fit::forward<Projection>(p), fit::forward<Filler>(f))
    )
};

}

FIT_STATIC_FUNCTION(transform) = fit::pipable(detail::algo<detail::transform_a>());

namespace view {

FIT_STATIC_FUNCTION(transform) = fit::pipable(detail::make_view<detail::transform_a>());

}

}

#endif
