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
#include <fit/by.hpp>
#include <fit/placeholders.hpp>
#include <fit/compress.hpp>
#include <fit/function.hpp>
#include <fit/construct.hpp>
#include <fit/decay.hpp>
#include <hero/detail/ordered.h>
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
: detail::closure<typename detail::gen_index_lookup<sizeof...(Ts)>::type, Ts...>, detail::ordered<tuple<Ts...>>
{
    typedef detail::closure<typename detail::gen_index_lookup<sizeof...(Ts)>::type, Ts...> base;
    FIT_INHERIT_CONSTRUCTOR(tuple, base)
    // TODO: Add implict conversions

    FIT_RETURNS_CLASS(tuple)

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

FIT_STATIC_FUNCTION(make_tuple) = fit::construct<tuple>();
FIT_STATIC_FUNCTION(forward_as_tuple) = fit::construct_forward<tuple>();

FIT_STATIC_FUNCTION(as_tuple) = fit::unpack(make_tuple);

template<class... Ts>
constexpr auto operator==(const tuple<Ts...>& x, const tuple<Ts...>& y) FIT_RETURNS
(
    tuple<Ts...>::unpack_zip(x, y, fit::compress(fit::_ and fit::_, true), fit::_ == fit::_)
);

template<class... Ts>
constexpr auto operator<(const tuple<Ts...>& x, const tuple<Ts...>& y) FIT_RETURNS
(
    tuple<Ts...>::unpack_zip(x, y, fit::compress(detail::lexical_compare_fold(), 0), detail::lexical_compare_each()) == -1
);

}

#endif