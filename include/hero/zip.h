/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    zip.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HERO_GUARD_ZIP_H
#define HERO_GUARD_ZIP_H

#include <hero/detail/algo.h>
#include <hero/detail/view.h>
#include <fit/rotate.hpp>
#include <fit/pipable.hpp>
#include <fit/combine.hpp>
#include <fit/by.hpp>

namespace hero { namespace detail {

template<class F>
struct zip_by_projection
{
    F f;
    FIT_DELGATE_CONSTRUCTOR(zip_by_projection, F, f)

    template<class T>
    constexpr auto operator()(T&& x) const FIT_RETURNS
    (
        fit::capture_forward(fit::forward<T>(x))(fit::rotate(f))
    )
};

struct zip_with_a
{
    template<class Filler, class Sequence, class Projection>
    constexpr auto operator()(Filler&& f, Sequence&& s, Projection p) const FIT_RETURNS
    (
        fit::unpack(
            fit::by(zip_by_projection<Projection>(p), fit::capture(fit::forward<Filler>(f))(fit::combine))
        )(fit::forward<Sequence>(s))
    )
};

struct zip_a
{
    template<class Filler, class Sequence>
    constexpr auto operator()(Filler&& f, Sequence&& s) const FIT_RETURNS
    (
        zip_with_a()(fit::forward<Sequence>(s), fit::pack)
    )
};

}

FIT_STATIC_FUNCTION(zip_with) = fit::pipable(detail::algo<detail::zip_with_a>());
FIT_STATIC_FUNCTION(zip) = fit::pipable(detail::algo<detail::zip_a>());

namespace view {

FIT_STATIC_FUNCTION(zip_with) = fit::pipable(detail::make_view<detail::zip_with_a>());
FIT_STATIC_FUNCTION(zip) = fit::pipable(detail::make_view<detail::zip_a>());

}

}

#endif