#ifndef _INT_TYPES_H
#define _INT_TYPES_H

// ToDo(robin): do this stuff myself
// ToDo(robin): does fuck up?
// #include <cinttypes>
#include <inttypes.h>

namespace flr {
// sigend integer types
// #ifdef __int8_t_defined
    typedef int8_t s8;
// #endif

// #ifdef __int16_t_defined
    typedef int16_t s16;
// #endif

// #ifdef __int32_t_defined
    typedef int32_t s32;
// #endif

// #ifdef __int64_t_defined
    typedef int64_t s64;
// #endif

// unsigned integer types
// #ifdef __uint8_t_defined
    typedef uint8_t u8;
// #endif

// #ifdef __uint16_t_defined
    typedef uint16_t u16;
// #endif

// #ifdef __uint32_t_defined
    typedef uint32_t u32;
// #endif

// #ifdef __uint64_t_defined
    typedef uint64_t u64;
// #endif
}

#endif
