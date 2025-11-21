/* date = July 29th 2025 6:43 pm */

#ifndef DEBUG_H
#define DEBUG_H

#if defined(DEBUG)

#define ASSERT_DEBUG(expression) if(!(expression)) *((int*)0)=0

#if defined(WIN32)
#define DEBUG_PRINT(x) OutputDebugStringA(x)
#endif //WIN_32

#else

#define ASSERT_DEBUG(expression)
#define DEBUG_PRINT(x)

#endif //DEBUG

#endif //DEBUG_H
