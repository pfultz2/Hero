/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    struct.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HERO_GUARD_STRUCT_H
#define HERO_GUARD_STRUCT_H

#define HERO_PP_CAT(x, ...) HERO_PP_PRIMITIVE_CAT(x, __VA_ARGS__)
#define HERO_PP_PRIMITIVE_CAT(x, ...) x ## __VA_ARGS__

#define HERO_PP_SEQ_ITERATE(...) HERO_PP_SEQ_PRIMITIVE_ITERATE(__VA_ARGS__)
#define HERO_PP_SEQ_PRIMITIVE_ITERATE(...) __VA_ARGS__ ## _END

#define HERO_PP_HEAD(...) HERO_PP_PRIMITIVE_HEAD(__VA_ARGS__, ~)
#define HERO_PP_PRIMITIVE_HEAD(x, ...) x

#define HERO_PP_TAIL(x, ...) __VA_ARGS__

#define HERO_PP_REM(...) __VA_ARGS__
#define HERO_PP_EAT(...)

// Retrieve the type
#define HERO_PP_TYPEOF(x) HERO_PP_PAIR(HERO_PP_HEAD(HERO_PP_TYPEOF_PROBE x))
#define HERO_PP_TYPEOF_PROBE(...) (__VA_ARGS__),
// Strip off the type
#define HERO_PP_STRIP(x) HERO_PP_EAT x
// Show the type without parenthesis
#define HERO_PP_PAIR(x) HERO_PP_REM x

#define HERO_PP_ENUM_SEQ(seq) HERO_PP_SEQ_ITERATE(HERO_PP_ENUM_SEQ_1 seq)
#define HERO_PP_ENUM_SEQ_1(x, ...) __VA_ARGS__ HERO_PP_ENUM_SEQ_2
#define HERO_PP_ENUM_SEQ_2(x, ...) , __VA_ARGS__ HERO_PP_ENUM_SEQ_3
#define HERO_PP_ENUM_SEQ_3(x, ...) , __VA_ARGS__ HERO_PP_ENUM_SEQ_2
#define HERO_PP_ENUM_SEQ_END

#define HERO_PP_ACCESS_FIELDS_EACH(...) s.HERO_PP_STRIP(HERO_PP_HEAD(__VA_ARGS__))
#define HERO_PP_ACCESS_FIELDS(seq) HERO_PP_SEQ_ITERATE(HERO_PP_ACCESS_FIELDS_1 seq)
#define HERO_PP_ACCESS_FIELDS_1(...) HERO_PP_ACCESS_FIELDS_EACH(__VA_ARGS__) HERO_PP_ACCESS_FIELDS_2
#define HERO_PP_ACCESS_FIELDS_2(...) HERO_PP_ACCESS_FIELDS_EACH(__VA_ARGS__) HERO_PP_ACCESS_FIELDS_1
#define HERO_PP_ACCESS_FIELDS_END

#define HERO_PP_STRUCT_DECLARE_FIELDS_EACH(...) HERO_PP_PAIR(HERO_PP_HEAD(__VA_ARGS__));
#define HERO_PP_STRUCT_DECLARE_FIELDS(seq) HERO_PP_SEQ_ITERATE(HERO_PP_STRUCT_DECLARE_FIELDS_1 seq)
#define HERO_PP_STRUCT_DECLARE_FIELDS_1(...) HERO_PP_STRUCT_DECLARE_FIELDS_EACH(__VA_ARGS__) HERO_PP_STRUCT_DECLARE_FIELDS_2
#define HERO_PP_STRUCT_DECLARE_FIELDS_2(...) HERO_PP_STRUCT_DECLARE_FIELDS_EACH(__VA_ARGS__) HERO_PP_STRUCT_DECLARE_FIELDS_1
#define HERO_PP_STRUCT_DECLARE_FIELDS_END

#define HERO_PP_STRUCT_ENUM_FIELDS(seq) HERO_PP_ENUM_SEQ(HERO_PP_ACCESS_FIELDS(seq))

#define HERO_STRUCT_TUPLE_FIELDS(seq) \
HERO_PP_STRUCT_DECLARE_FIELDS(seq) \
struct hero_unpack_sequence \
{ \
    template<class F, class S> \
    constexpr static auto apply(F&& f, S&& s) FIT_RETURNS \
    ( \
        f(HERO_PP_STRUCT_ENUM_FIELDS(seq)) \
    ); \
};
 
#define HERO_STRUCT_TUPLE_ADAPT_STRUCT(name, seq) \
namespace fit { \
template<class T> \
struct unpack_sequence<name> \
{ \
    template<class F, class P> \
    constexpr static auto apply(F&& f, P&& p) FIT_RETURNS \
    ( \
        f(HERO_PP_STRUCT_ENUM_FIELDS(seq)) \
    ); \
}; \
}

namespace hero {



}

#endif