/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    always_void.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HERO_GUARD_ALWAYS_VOID_H
#define HERO_GUARD_ALWAYS_VOID_H

namespace hero { namespace detail {

template<class...>
struct always_void
{ typedef void type; };

}

}

#endif