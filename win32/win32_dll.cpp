
// NOTE(Banni): Gets the last write time for a file
inline FILETIME
Win32GetLastWriteTime(const char *FileName)
{
    FILETIME LastWriteTime = {};
    
    WIN32_FILE_ATTRIBUTE_DATA Data;
    if(GetFileAttributesEx(FileName, GetFileExInfoStandard, &Data))
    {
        LastWriteTime = Data.ftLastWriteTime;
    }
    
    return LastWriteTime;
}

#define GAME_DLL_NAME "game.dll"
#define GAME_TEMP_DLL_NAME "game_temp.dll"

// NOTE(Banni): Loads the game DLL
internal win32_game_code
Win32LoadGameDLL(b32 Loop)
{
    win32_game_code Result = {};
    Result.LastWriteTime = Win32GetLastWriteTime(GAME_DLL_NAME);
    while(CopyFile(GAME_DLL_NAME, GAME_TEMP_DLL_NAME, FALSE) == 0 && Loop)
    {
        
    }
    
    Result.GameCodeDLL = LoadLibraryA(GAME_TEMP_DLL_NAME);
    
    if(Result.GameCodeDLL)
    {
        Result.GameUpdate = (game_update*)GetProcAddress(Result.GameCodeDLL,
                                                         "GameUpdate");
        Result.Valid = Result.GameUpdate != NULL;
    }
    
    if(!Result.Valid)
    {
        Result.GameUpdate = GameUpdateStub;
        DEBUG_PRINT("Failed to load game DLL");
    }
    
    return Result;
}

// NOTE(Banni): Unloads the game code
internal void 
Win32UnloadGameDLL(win32_game_code* GameCode)
{
    if(GameCode->GameCodeDLL)
    {
        FreeLibrary(GameCode->GameCodeDLL);
        GameCode->Valid = false;
    }
    GameCode->GameUpdate = GameUpdateStub;
}
