/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    reverse_fold.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HERO_GUARD_REVERSE_FOLD_H
#define HERO_GUARD_REVERSE_FOLD_H

#include <hero/detail/algo.h>
#include <fit/reverse_compress.hpp>
#include <fit/pipable.hpp>

namespace hero {

FIT_STATIC_FUNCTION(reverse_fold) = fit::pipable(fit::limit_c<3>(detail::make_algo_action(fit::reverse_compress)));

}

#endif
