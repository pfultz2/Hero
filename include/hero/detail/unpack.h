/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    unpack.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HERO_GUARD_UNPACK_H
#define HERO_GUARD_UNPACK_H

#include <fit/unpack.hpp>

namespace fit {
// TODO: Use REQUIRES_EXIST
template<class T>
struct unpack_sequence<T, typename detail::holder<
    typename T::hero_unpack_sequence
>::type>
{
    template<class F, class P>
    constexpr static auto apply(F&& f, P&& p) FIT_RETURNS
    (
        T::hero_unpack_sequence::apply(fit::forward<F>(f), fit::forward<P>(p))
    );
};

}

#endif
