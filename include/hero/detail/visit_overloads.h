/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    visit_overloads.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HERO_GUARD_VISIT_OVERLOADS_H
#define HERO_GUARD_VISIT_OVERLOADS_H

#include <fit/returns.hpp>

namespace hero {

#define HERO_UNARY_PERFECT_ID(...) __VA_ARGS__
#define HERO_UNARY_PERFECT_FOREACH(m) \
    m(const&, HERO_UNARY_PERFECT_ID) \
    m(&, HERO_UNARY_PERFECT_ID) \
    m(&&, fit::move) \

}

#endif