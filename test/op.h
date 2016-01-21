
#include <iostream>
#include <fit/unpack.hpp>
#include <fit/lazy.hpp>
#include <fit/placeholders.hpp>
#include <hero/for_each.h>

struct tuple_factory
{
    template<class... Ts>
    auto operator()(Ts&&... xs) const
    {
        return std::make_tuple(std::forward<Ts>(xs)...);
    }
};

template<class T>
auto as_tuple(T&& x)
{
    return fit::unpack(tuple_factory())(std::forward<T>(x));
}

template<class... Ts>
std::ostream& operator<<(std::ostream& os, const std::tuple<Ts...>& t)
{
    os << "[";
    hero::for_each(t, [&](const auto& x)
    {
        os << x << ", ";
    });
    os << "]";
    return os;
}
