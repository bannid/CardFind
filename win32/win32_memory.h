/* date = July 29th 2025 7:23 pm */

#ifndef WIN32_MEMORY_H
#define WIN32_MEMORY_H

#define Win32_Get_Memory(Size) VirtualAlloc(NULL, Size, MEM_COMMIT, PAGE_READWRITE)
#define Win32_Free_Memory(Pointer, Size) VirtualFree(ptr, size, MEM_RELEASE)

#endif //WIN32_MEMORY_H
