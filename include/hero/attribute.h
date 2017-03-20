/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    attribute.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HERO_GUARD_ATTRIBUTE_H
#define HERO_GUARD_ATTRIBUTE_H

#include <hero/pair.h>
#include <hero/map.h>
#include <fit/fix.hpp>
#include <tick/requires.h>

namespace hero {

namespace detail {

template<class T>
struct attribute_storage
{
    static constexpr T value = T();
};

template<class T>
constexpr T attribute_storage<T>::value;

template<class T>
constexpr const T& attribute_var(const T&)
{
    static_assert(std::is_default_constructible<T>::value, "Attribute must be default constructible");
    return detail::attribute_storage<T>::value;
}

struct attribute_result_base
{};

template<class F, class=void>
struct attribute_result : attribute_result_base
{
    template<class Self, class... Ts>
    constexpr auto operator()(const Self& s, Ts&&... xs) const FIT_RETURNS
    (
        make_pair(fit::fix(s.base_function().base_function()), F()(fit::forward<Ts>(xs)...))
    );
};

template<class F, class T, class G, class U>
inline tick::integral_constant<bool, (std::is_same<attribute_result<F, T>, attribute_result<G, U>>::value)> 
operator==(const attribute_result<F, T>&, const attribute_result<G, U>&)
{
    return {};
}
template<class F, class T, class U, TICK_REQUIRES(
    !std::is_base_of<attribute_result_base, U>::value
)>
inline tick::false_type operator==(const attribute_result<F, T>&, const U&)
{
    return {};
}
template<class F, class T, class U, TICK_REQUIRES(
    !std::is_base_of<attribute_result_base, U>::value
)>
inline tick::false_type operator==(const U&, const attribute_result<F, T>&)
{
    return {};
}

template<class F, class T, class G, class U>
inline tick::integral_constant<bool, (!std::is_same<attribute_result<F, T>, attribute_result<G, U>>::value)> 
operator!=(const attribute_result<F, T>&, const attribute_result<G, U>&)
{
    return {};
}
template<class F, class T, class U, TICK_REQUIRES(
    !std::is_base_of<attribute_result_base, U>::value
)>
inline tick::true_type operator!=(const attribute_result<F, T>&, const U&)
{
    return {};
}
template<class F, class T, class U, TICK_REQUIRES(
    !std::is_base_of<attribute_result_base, U>::value
)>
inline tick::true_type operator!=(const U&, const attribute_result<F, T>&)
{
    return {};
}

struct attribute_f
{
    template<class F>
    constexpr auto operator()(const F& f) const FIT_RETURNS
    (
        attribute_var(fit::fix(attribute_result<F>()))
    );
};

template<class T>
struct attribute_factory
{
    constexpr attribute_factory()
    {}
    template<class F>
    constexpr auto operator=(const F&) const FIT_RETURNS
    (
        attribute_var(fit::fix(attribute_result<F, T>()))
    );
};

struct attribute_id
{
    template<class First, class Second>
    static pair<First, Second> deduce_pair(const pair<First, Second>& p);
    template<class Pair>
    constexpr auto operator()(Pair&& p) const -> decltype(deduce_pair(p))
    {
        return p;
    }
};

struct attribute_pair
{
    template<class T>
    constexpr auto operator()(T&& x) const FIT_RETURNS
    (
        make_pair(x, x)
    );
};

}

#if FIT_NO_UNIQUE_STATIC_VAR
#define HERO_DETAIL_DECLARE_ATTRIBUTE_VAR(name) FIT_STATIC_CONSTEXPR auto name = FIT_DETAIL_MSVC_CONSTEXPR_DEDUCE
#else
#define HERO_DETAIL_DECLARE_ATTRIBUTE_VAR(name) FIT_STATIC_AUTO_REF name = 
#endif

#define HERO_ATTRIBUTE(name) \
struct hero_private_attribute_ ## name {}; \
HERO_DETAIL_DECLARE_ATTRIBUTE_VAR(name) hero::detail::attribute_factory<hero_private_attribute_ ## name>()

HERO_ATTRIBUTE(field_name) = fit::construct<const char*>();

FIT_STATIC_FUNCTION(attribute) = detail::attribute_f();

FIT_STATIC_FUNCTION(make_attr_map) = fit::by(
    fit::conditional(detail::attribute_id(), detail::attribute_pair()), 
    make_map
);

} // namespace hero

#endif
