/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    join.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HERO_GUARD_JOIN_H
#define HERO_GUARD_JOIN_H

#include <hero/detail/algo.h>
#include <hero/detail/view.h>
#include <fit/pipable.hpp>
#include <fit/compose.hpp>

namespace hero { namespace detail {

struct join_f
{
    template<class S, class... Ss>
    constexpr auto operator()(S&& s, Ss&&... ss) const FIT_RETURNS
    (
        fit::unpack(fill(s))(fit::forward<S>(s), fit::forward<Ss>(ss)...)
    )
};

template<class A>
struct join_view : A
{
    FIT_INHERIT_CONSTRUCTOR(join_view, A)
    struct hero_unpack_sequence
    {
        template<class F, class S>
        constexpr static auto apply(F&& f, S&& s) FIT_RETURNS
        (
            s(fit::unpack(f))()
        );
    };
};

struct make_view_f
{
    template<class A>
    constexpr join_view<A> operator()(A a) const
    {
        return join_view<A>(fit::move(a));
    }
};

}

FIT_STATIC_FUNCTION(join) = detail::join_f();

namespace view {

FIT_STATIC_FUNCTION(join) = fit::compose(detail::make_view_f(), fit::capture);

}

}

#endif
