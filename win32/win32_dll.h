/* date = July 30th 2025 7:45 pm */

#ifndef WIN32_DLL_H
#define WIN32_DLL_H

struct win32_game_code
{
    HMODULE GameCodeDLL;
    game_update* GameUpdate;
    b32 Valid;
    FILETIME LastWriteTime;
};

#endif //WIN32_DLL_H
