/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    ordered.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HERO_GUARD_ORDERED_H
#define HERO_GUARD_ORDERED_H

#include <hero/detail/always_void.h>
#include <fit/returns.hpp>
#include <utility>

namespace hero { namespace detail {

// TODO: support dependent typing
struct lexical_compare_each
{
    template<class T, class U>
    constexpr auto operator()(const T& x, const U& y) const FIT_RETURNS
    (
        (x < y) ? -1 :
        (y < x) ? 1 : 
        0
    );
};

struct lexical_compare_fold
{
    template<class T, class U>
    constexpr T operator()(T x, U y) const
    {
        return x == 0 ? y : x;
    }
};

template<class T>
struct ordered
{
    template<class U=T>
    constexpr friend auto operator!=(const T& x, const U& y) -> decltype((x == y), bool()) 
    { return !static_cast<bool>(x == y); }
    template<class U=T>
    constexpr friend auto operator>(const T& x, const U& y) -> decltype((y < x), bool()) 
    { return y < x; }
    template<class U=T>
    constexpr friend auto operator<=(const T& x, const U& y) -> decltype((x < y), (x == y), bool()) 
    { return static_cast<bool>(x < y) || static_cast<bool>(x == y); }
    template<class U=T>
    constexpr friend auto operator>=(const T& x, const U& y) -> decltype((y < x), (x == y), bool()) 
    { return static_cast<bool>(y < x) || static_cast<bool>(x == y); }

    template<class U, typename std::enable_if<(!std::is_same<T, U>::value)>::type>
    constexpr friend auto operator==(const U& y, const T& x) -> decltype((x == y), bool()) 
    { return x == y; }
    template<class U, typename std::enable_if<(!std::is_same<T, U>::value)>::type>
    constexpr friend auto operator!=(const U& y, const T& x) -> decltype((x == y), bool()) 
    { return !static_cast<bool>(x == y); }

    template<class U, typename std::enable_if<(!std::is_same<T, U>::value)>::type>
    constexpr friend auto operator>(const U& x, const T& y) -> decltype((y < x), bool())
    { return y < x; }
    template<class U, typename std::enable_if<(!std::is_same<T, U>::value)>::type>
    constexpr friend auto operator<(const U& x, const T& y) -> decltype((y > x), bool())
    { return y > x; }
    template<class U, typename std::enable_if<(!std::is_same<T, U>::value)>::type>
    constexpr friend auto operator<=(const U& x, const T& y) -> decltype((y > x), (y == x), bool())
    { return static_cast<bool>(y > x) || static_cast<bool>(y == x); }
    template<class U, typename std::enable_if<(!std::is_same<T, U>::value)>::type>
    constexpr friend auto operator>=(const U& x, const T& y) -> decltype((y < x), (y == x), bool())
    { return static_cast<bool>(y < x) || static_cast<bool>(y == x); }


};

}

}

#endif