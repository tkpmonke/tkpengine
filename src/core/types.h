#pragma once

#if !defined(PACKED)
	#if defined(__GNUC__)
		#define PACKED __attribute__((__packed__))
	#else
		#define PACKED
	#endif
#endif

#if !defined(TRUE)
	#define TRUE 1
#endif

#if !defined(FALSE)
	#define FALSE 0
#endif

#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef i8 schar;
typedef u8 uchar;
typedef u8 boolean;

typedef u64 length;
typedef i64 ilength;

typedef float f32;
typedef double f64;

/*
 * f128 is supported on some compilers but
 * due to the compilers that don't support it (msvc)
 * and it not really being necessary, it's not
 * included here
 */

typedef char* string;
typedef u64 hashed_string;
