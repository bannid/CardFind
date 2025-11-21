/* date = March 5th 2025 5:17 pm */

#ifndef UTILS_H
#define UTILS_H
#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a > b ? a : b)
#define CLAMP(x, a, b) MAX(a, MIN(b, x))
#define FMIN(a, b) MIN(a, b)
#define FMAX(a, b) MAX(a, b)
#define KILOBYTE(x) (1024 * x)
#define MEGABYTE(x) (KILOBYTE(1024) * x)
#define GIGABYTE(x) (MEGABYTE(1024) * x)
#define PI 3.141592

#define ARRAY_COUNT(x) sizeof(x) / sizeof(x[0])
#define DECLARE_LIST(type)\
struct type##_list {\
u32 Size;\
u32 Length;\
b32 Initialized;\
type* Items;\
}

// NOTE(Banni): Functions that uses scratch arena.
// Scratch arenas are normal arenas, however, they are
// passed in as non pointers, which means the function
// cannot change the state of arenas.
#define UsesScratchArena

#endif  // UTILS_H
