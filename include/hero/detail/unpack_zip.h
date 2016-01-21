/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    unpack_zip.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HERO_GUARD_UNPACK_ZIP_H
#define HERO_GUARD_UNPACK_ZIP_H

#include <fit/by.hpp>
#include <fit/combine.hpp>
#include <fit/capture.hpp>
#include <fit/unpack.hpp>

namespace hero { namespace detail {

struct zip_projection
{
    template<class F, class T>
    constexpr auto operator()(F f, T&& x) const FIT_RETURNS
    (
        fit::capture_forward(fit::forward<T>(x))(fit::move(f))
    )
};

template<class T, class U, class F, class P>
constexpr auto unpack_zip(T&& x, U&& y, F f, P p) FIT_RETURNS
(
    fit::unpack(
        fit::unpack(
            fit::by(fit::capture(fit::move(p))(zip_projection()), fit::capture(fit::move(f))(fit::combine))
        )(fit::forward<T>(x))
    )(fit::forward<U>(y))
);

}}

#endif