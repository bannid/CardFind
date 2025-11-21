/* date = July 29th 2025 6:35 pm */

#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <stddef.h>
#include <limits.h>
#include <float.h>

typedef glm::vec4 v4;
typedef glm::vec3 v3;
typedef glm::vec2 v2;
typedef glm::mat4 mat4;
typedef glm::ivec2 iv2;
typedef glm::quat quat;
typedef v4 col4;
typedef v3 col3;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
typedef int32 bool32;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef intptr_t intptr;
typedef uintptr_t uintptr;

typedef size_t memory_index;

typedef float real32;
typedef double real64;

typedef int8 s8;
typedef int8 s08;
typedef int16 s16;
typedef int32 s32;
typedef int64 s64;
typedef bool32 b32;

typedef uint8 u8;
typedef uint8 u08;
typedef uint16 u16;
typedef uint32 u32;
typedef uint64 u64;

typedef real32 r32;
typedef real32 f32;
typedef real64 r64;
typedef unsigned char uchar;
#define global static
#define internal static
#define local_persist static

#endif //TYPES_H