/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    filter.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HERO_GUARD_FILTER_H
#define HERO_GUARD_FILTER_H

#include <hero/detail/algo.h>
#include <hero/detail/view.h>
#include <fit/pipable.hpp>
#include <fit/by.hpp>
#include <fit/if.hpp>

namespace hero { namespace detail {

template<class Predicate>
struct filter_projection
{
    // TODO: Check that the predicate result is an integral constant
    template<class T>
    constexpr static decltype(std::declval<Predicate>()(std::declval<T>())) 
    predicate(T&&)
    {
        typedef decltype(std::declval<Predicate>()(std::declval<T>())) p;
        return {};
    }
    template<class T>
    constexpr auto operator()(T&& x) const FIT_RETURNS
    (
        fit::conditional(
            fit::if_(predicate(fit::forward<T>(x)))(fit::pack),
            fit::always(fit::pack())
        )(fit::forward<T>(x))
    )
};

struct filter_a
{
    template<class Filler, class Predicate>
    constexpr auto operator()(Filler&& f, const Predicate&) const FIT_RETURNS
    (
        fit::by(filter_projection<Predicate>(), fit::unpack(fit::forward<Filler>(f)))
    )
};

}

FIT_STATIC_FUNCTION(filter) = fit::pipable(detail::algo<detail::filter_a>());

namespace view {

FIT_STATIC_FUNCTION(filter) = fit::pipable(detail::make_view<detail::filter_a>());

}

}

#endif