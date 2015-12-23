#include <hero/map.h>
#include "test.h"

struct first_key
{};

struct second_key
{};

struct third_key
{};

PROVE_CASE()
{
    auto m = hero::make_map(
        hero::make_pair(first_key(), 1),
        hero::make_pair(second_key(), 2),
        hero::make_pair(third_key(), 3)
    );

    PROVE_CHECK(m[first_key()] == 1);
    PROVE_CHECK(m[second_key()] == 2);
    PROVE_CHECK(m[third_key()] == 3);
}

PROVE_CASE()
{
    auto m = hero::make_map();
    PROVE_CHECK(m.size() == 0);
    PROVE_STATIC_CHECK(m.size() == 0);

    PROVE_CHECK(m.empty());
    PROVE_STATIC_CHECK(m.empty());
}

