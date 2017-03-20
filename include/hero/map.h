/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    map.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HERO_GUARD_MAP_H
#define HERO_GUARD_MAP_H

#include <hero/pair.h>

namespace hero {

template<class... Ts>
struct map;

template<class... Keys, class... Values>
struct map<pair<Keys, Values>...>
: detail::closure<detail::lookup<Keys...>, pair<Keys, Values>...>, detail::ordered<map<pair<Keys, Values>...>>
{
    typedef detail::closure<detail::lookup<Keys...>, pair<Keys, Values>...> base;
    FIT_INHERIT_CONSTRUCTOR(map, base)
    // TODO: Add implict conversions

    FIT_RETURNS_CLASS(map)

    template<class Key>
    constexpr auto operator[](Key) const FIT_RETURNS
    (second(base::template get_by_key<Key>(*FIT_CONST_THIS)))

    template<class Key>
    constexpr auto operator[](Key) FIT_RETURNS
    (second(base::template get_by_key<Key>(*FIT_THIS)))

    constexpr tick::integral_constant<std::size_t, sizeof...(Values)> size() const
    {
        return {};
    }

    constexpr tick::integral_constant<bool, sizeof...(Values) == 0> empty() const
    {
        return {};
    }

    template<class Stream>
    friend Stream& operator<<(Stream& os, const map& t)
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

FIT_STATIC_FUNCTION(make_map) = fit::construct<map>();

FIT_STATIC_FUNCTION(as_map) = fit::unpack(make_map);

template<class... Ts>
constexpr auto operator==(const map<Ts...>& x, const map<Ts...>& y) FIT_RETURNS
(
    map<Ts...>::unpack_zip(x, y, fit::compress(fit::_ and fit::_, true), fit::_ == fit::_)
);

template<class... Ts>
constexpr auto operator<(const map<Ts...>& x, const map<Ts...>& y) FIT_RETURNS
(
    map<Ts...>::unpack_zip(x, y, fit::compress(detail::lexical_compare_fold(), 0), detail::lexical_compare_each()) == -1
);

}

#endif