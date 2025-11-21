/* date = October 19th 2025 10:55 am */

#ifndef ARENA_H
#define ARENA_H

#define ARENA_IS_VALID(A)       ASSERT_DEBUG((A).Initialized && !(A).Freed)
#define ARENA_HAS_MEMORY(A,S)   ASSERT_DEBUG((A).Offset + S <= (A).Size)

// Note(Banni): A simple non-growable memory arena
struct memory_arena
{
    void*                       BasePointer;    // Note(Banni): Pointer to the base of the allocated memory
    u32                         Offset;         // Note(Banni): How much memory has been allocted
    u32                         Size;           // Note(Banni): Size of the arena
    b32                         Freed;          // Note(Banni): If the arena has been freed
    b32                         Initialized;    // Note(Banni): If the arena is initialized
};


#endif //ARENA_H
