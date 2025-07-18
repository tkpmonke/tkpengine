#pragma once

#include <stdint.h>
#include <stdlib.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef u8 boolean;

typedef u64 length;
typedef i64 ilength;

typedef float f32;
typedef double f64;

/*
 * f128 is supported on some compilers but
 * due to the compilers that don't support it (msvc)
 * and it not really being nessesarry, its not
 * included here
 */

typedef char* string;

