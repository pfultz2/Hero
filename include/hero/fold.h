/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    fold.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HERO_GUARD_FOLD_H
#define HERO_GUARD_FOLD_H

#include <fit/unpack.h>
#include <fit/pipable.h>
#include <fit/by.h>
#include <fit/fix.h>
#include <fit/match.h>
#include <fit/function.h>
#include <tick/requires.h>

namespace hero {

namespace detail {

FIT_STATIC_FUNCTION(fold_each) = fit::fix(fit::match(
        [](auto self, auto&& f, auto&& state, auto&& x, auto&&... xs) -> decltype(auto)
        {
            return self(f, f(FIT_AUTO_FORWARD(state), FIT_AUTO_FORWARD(x)), FIT_AUTO_FORWARD(xs)...);
        },
        [](auto self, auto&& f, auto&& state) -> decltype(auto)
        {
            return FIT_AUTO_FORWARD(state);
        }
    ));

FIT_STATIC_FUNCTION(fold_each_pop) = fit::match(
        [](auto&& f, auto&& x, auto&&... xs) -> decltype(auto)
        {
            return fold_each(f, FIT_AUTO_FORWARD(x), FIT_AUTO_FORWARD(xs)...);
        }
    );

}

FIT_STATIC_FUNCTION(fold) = fit::pipable(fit::match(
    [](auto&& seq, auto f, TICK_PARAM_REQUIRES(tick::trait<fit::is_unpackable>(seq)))
    {
        return fit::unpack(fit::capture_forward(f)(detail::fold_each_pop))(seq);
    },
    [](auto&& seq, auto&& state, auto f, TICK_PARAM_REQUIRES(tick::trait<fit::is_unpackable>(seq)))
    {
        return fit::unpack(fit::capture_forward(f, FIT_AUTO_FORWARD(state))(detail::fold_each))(seq);
    }
));

}

#endif
