#include <hero/attribute.h>
#include "test.h"

HERO_ATTRIBUTE(my_name) = fit::construct<std::string>();

PROVE_CASE()
{
    auto p = hero::field_name("name");
    static_assert(std::is_same<
        typename std::decay<decltype(hero::first(p))>::type, 
        typename std::decay<decltype(hero::field_name)>::type
    >::value, "Error");
    PROVE_CHECK(bool{hero::first(p) == hero::field_name});
    PROVE_CHECK(bool{hero::first(p) != my_name});
    PROVE_CHECK(bool{not(hero::first(p) != hero::field_name)});
    PROVE_CHECK(hero::second(p) == std::string("name"));
}
