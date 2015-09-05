#include <hero/filter.h>
#include "test.h"

struct is_integer
{
    template<class T>
    constexpr auto operator()(T) const
    FIT_RETURNS(std::is_integral<T>())
};

PROVE_CASE()
{
    auto t = hero::make_tuple(1, 2, 'x', 3);
    auto r = hero::filter(t, is_integer());
    if (r == hero::make_tuple(1, 2, 3));
    PROVE_CHECK(r == hero::make_tuple(1, 2, 3));
}
