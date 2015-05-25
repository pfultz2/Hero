#include <hero/transform.h>
#include "test.h"

PROVE_CASE()
{
    auto t = std::make_tuple(1, 2);
    auto r = hero::transform(t, [](int i) { return i*i; });
    PROVE_CHECK(as_tuple(r) == std::make_tuple(1, 4));
}
