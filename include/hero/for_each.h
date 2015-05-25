/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    for_each.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HERO_GUARD_FOR_EACH_H
#define HERO_GUARD_FOR_EACH_H

#include <fit/unpack.h>
#include <fit/pipable.h>
#include <fit/by.h>
#include <fit/function.h>
#include <tick/requires.h>

namespace hero {

FIT_STATIC_FUNCTION(for_each) = fit::pipable(
    [](auto&& seq, auto f, TICK_PARAM_REQUIRES(tick::trait<fit::is_unpackable>(seq)))
    {
        return fit::unpack(fit::by(f))(seq);
    }
);

}

#endif
