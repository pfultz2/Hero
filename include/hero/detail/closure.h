/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    closure.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HERO_GUARD_CLOSURE_H
#define HERO_GUARD_CLOSURE_H

#include <fit/alias.h>

namespace hero { namespace detail {

template<class...>
struct closure_tag
{};

#define HERO_CLOSURE_HAS_EBO 1
#if HERO_CLOSURE_HAS_EBO
template<class T, class Tag>
struct closure_holder
: std::conditional<std::is_empty<T>::value, 
    fit::alias_inherit<T, Tag>, 
    fit::alias<T, Tag>
>
{};
#else
template<class T, class Tag>
struct closure_holder
: std::conditional<
        std::is_empty<T>::value && 
        std::is_literal_type<T>::value && 
        std::is_default_constructible<T>::value, 
    fit::alias_static<T, Tag>,
    fit::alias<T, Tag>
>
{};
#endif

template<class...>
struct closure;

template<class...>
struct lookup
{};

template<class... Keys, class... Ts>
struct closure<lookup<Keys...>, Ts...>
: closure_holder<Ts, closure_tag<Keys, Ts...>>::type...
{
    FIT_INHERIT_DEFAULT(closure, typename std::remove_cv<typename std::remove_reference<Ts>::type>::type...);
    
    template<class... Xs, FIT_ENABLE_IF_CONVERTIBLE_UNPACK(Xs&&, typename closure_holder<Ts, closure_tag<Keys, Ts...>>::type)>
    constexpr closure(Xs&&... xs) : closure_holder<Ts, closure_tag<Keys, Ts...>>::type(fit::forward<Xs>(xs))...
    {}

    // FIT_RETURNS(f(fit::alias_value<Ts, pack_tag<seq<Ns>, Ts...>>(move(x), f)...))

    template<class Key, class Self>
    constexpr static auto get_by_key(Self&& self) FIT_RETURNS
    (
        fit::alias_value<closure_tag<Key, Ts...>>(fit::forward<Self>(self))
    )

    template<class Key, class T, class Self>
    constexpr static auto get_element(Self&& self) FIT_RETURNS
    (
        fit::alias_value<closure_tag<Key, Ts...>, T>(fit::forward<Self>(self))
    )

    template<class Key, class T, class Self1, class Self2, class F>
    constexpr static auto unpack_zip_project(Self1&& s1, Self2&& s2, F f) FIT_RETURNS
    (
        f(
            fit::alias_value<closure_tag<Key, Ts...>, T>(fit::forward<Self1>(s1)), 
            fit::alias_value<closure_tag<Key, Ts...>, T>(fit::forward<Self2>(s2))
        )
    )

    template<class Self1, class Self2, class F, class Projection>
    constexpr static auto unpack_zip(Self1&& s1, Self2&& s2, F f, Projection p) FIT_RETURNS
    (
        f(unpack_zip_project<Keys, Ts>(fit::forward<Self1>(s1), fit::forward<Self2>(s2), p)...)
    )

    struct hero_unpack_sequence
    {
        template<class F, class P>
        constexpr static auto apply(F&& f, P&& p) FIT_RETURNS
        (
            f(get_element<Keys, Ts>(fit::forward<P>(p))...)
        )
    };
};

}

}

#endif