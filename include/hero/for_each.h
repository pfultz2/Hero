/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    for_each.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HERO_GUARD_FOR_EACH_H
#define HERO_GUARD_FOR_EACH_H

#include <hero/detail/algo.h>
#include <hero/detail/view.h>
#include <fit/pipable.hpp>
#include <fit/by.hpp>
#include <fit/if.hpp>

namespace hero { namespace detail {

struct for_each_a
{
    template<class Projection>
    constexpr auto operator()(Projection&& p) const
    {
        return fit::by(fit::forward<Projection>(p));
    }
};

struct for_each_view
{
    template<class Filler, class Projection>
    constexpr auto operator()(Filler&& f, Projection&& p) const FIT_RETURNS
    (
        fit::by(fit::forward<Projection>(p), fit::unpack(fit::forward<Filler>(f)))
    )
};

struct yield_if_f
{
    template<class C>
    constexpr auto operator()(C c) const FIT_RETURNS
    (
        fit::conditional(
            fit::if_(c)(fit::pack_decay),
            fit::always(fit::pack())
        )
    )
};

}

FIT_STATIC_FUNCTION(for_each) = fit::pipable(detail::algo_action<detail::for_each_a>());

FIT_STATIC_FUNCTION(yield) = fit::pack_decay;
FIT_STATIC_FUNCTION(yield_if) = detail::yield_if_f();

namespace view {

FIT_STATIC_FUNCTION(for_each) = fit::pipable(detail::make_view<detail::for_each_view>());

}

}

#endif
