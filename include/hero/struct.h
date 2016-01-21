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

#define HERO_PP_FIRST(...) HERO_PP_PRIMITIVE_FIRST(__VA_ARGS__, ~)
#define HERO_PP_PRIMITIVE_FIRST(x, ...) x

#define HERO_PP_TAIL(x, ...) __VA_ARGS__

#define HERO_STRUCT_ENUM_FIELDS_EACH(...) s.HERO_PP_FIRST(__VA_ARGS__)
#define HERO_STRUCT_ENUM_FIELDS(seq) HERO_PP_SEQ_ITERATE(HERO_STRUCT_ENUM_FIELDS_1 seq)
#define HERO_STRUCT_ENUM_FIELDS_1(x, ...) HERO_STRUCT_ENUM_FIELDS_EACH(__VA_ARGS__) HERO_STRUCT_ENUM_FIELDS_2
#define HERO_STRUCT_ENUM_FIELDS_2(x, ...) , HERO_STRUCT_ENUM_FIELDS_EACH(__VA_ARGS__) HERO_STRUCT_ENUM_FIELDS_3
#define HERO_STRUCT_ENUM_FIELDS_3(x, ...) , HERO_STRUCT_ENUM_FIELDS_EACH(__VA_ARGS__) HERO_STRUCT_ENUM_FIELDS_2
#define HERO_STRUCT_ENUM_FIELDS_END

#define HERO_STRUCT_DECLARE_FIELDS_EACH(...) HERO_PP_TAIL(__VA_ARGS__) HERO_PP_FIRST(__VA_ARGS__);
#define HERO_STRUCT_DECLARE_FIELDS(seq) HERO_PP_SEQ_ITERATE(HERO_STRUCT_DECLARE_FIELDS_1 seq)
#define HERO_STRUCT_DECLARE_FIELDS_1(x, ...) HERO_STRUCT_DECLARE_FIELDS_EACH(__VA_ARGS__) HERO_STRUCT_DECLARE_FIELDS_2
#define HERO_STRUCT_DECLARE_FIELDS_2(x, ...) HERO_STRUCT_DECLARE_FIELDS_EACH(__VA_ARGS__) HERO_STRUCT_DECLARE_FIELDS_1
#define HERO_STRUCT_DECLARE_FIELDS_END

#define HERO_STRUCT_TUPLE_FIELDS(seq) \
HERO_STRUCT_DECLARE_FIELDS(seq) \
struct hero_unpack_sequence \
{ \
    template<class F, class S> \
    constexpr static auto apply(F&& f, S&& s) FIT_RETURNS \
    ( \
        f(HERO_STRUCT_ENUM_FIELDS(seq)) \
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
        f(HERO_STRUCT_ENUM_FIELDS(seq)) \
    ); \
}; \ 
}

namespace hero {



}

#endif