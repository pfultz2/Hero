/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    tuple.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HERO_GUARD_TUPLE_H
#define HERO_GUARD_TUPLE_H

#include <hero/detail/closure.h>
#include <hero/detail/unpack.h>
#include <fit/by.h>
#include <fit/placeholders.h>
#include <fit/compress.h>
#include <fit/function.h>
#include <fit/construct.h>
#include <fit/decay.h>
#include <tick/integral_constant.h>

namespace hero { namespace detail {

template<int N, class ...S>
struct gen_index_lookup 
: gen_index_lookup<N-1, std::integral_constant<int, N-1>, S...> 
{};

template<class ...S>
struct gen_index_lookup<0, S...> 
{
  typedef lookup<S...> type;
};

}

template<class... Ts>
struct tuple
: detail::closure<typename detail::gen_index_lookup<sizeof...(Ts)>::type, Ts...>
{
    typedef detail::closure<typename detail::gen_index_lookup<sizeof...(Ts)>::type, Ts...> base;
    FIT_INHERIT_CONSTRUCTOR(tuple, base)
    // TODO: Add implict conversions

    template<class IntegralConstant>
    constexpr auto operator[](IntegralConstant) const FIT_RETURNS
    (base::template get_by_key<std::integral_constant<int, IntegralConstant::value>>(*FIT_CONST_THIS))

    template<class IntegralConstant>
    constexpr auto operator[](IntegralConstant) FIT_RETURNS
    (base::template get_by_key<std::integral_constant<int, IntegralConstant::value>>(*FIT_THIS))

    constexpr tick::integral_constant<std::size_t, sizeof...(Ts)> size() const
    {
        return {};
    }

    constexpr tick::integral_constant<bool, sizeof...(Ts) == 0> empty() const
    {
        return {};
    }

    template<class Stream>
    friend Stream& operator<<(Stream& os, const tuple& t)
    {
        os << "[";
        fit::unpack(fit::by([&](const auto& x)
        {
            os << x << ", ";
        }))(t);
        os << "]";
        return os;
    }
};

FIT_STATIC_FUNCTION(make_tuple) = fit::by(fit::decay, fit::construct<tuple>());

FIT_STATIC_FUNCTION(as_tuple) = fit::unpack(fit::construct<tuple>());

template<class... Ts>
constexpr bool operator==(const tuple<Ts...>& x, const tuple<Ts...>& y)
{
    return tuple<Ts...>::unpack_zip(x, y, fit::compress(fit::_ and fit::_), fit::_ == fit::_);
}

template<class... Ts>
constexpr bool operator!=(const tuple<Ts...>& x, const tuple<Ts...>& y)
{
    return !(x == y);
}

}

#endif