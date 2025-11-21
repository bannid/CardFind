int32 
Win32ReadEntireFileV2(const char* FileName,
                      u8* Buffer,
                      u32 BufferSize,
                      b32 NullTerminate)
{
    
    HANDLE Handle;
    u32 FileSize;
    Handle = CreateFileA(
                         FileName,
                         GENERIC_READ,
                         FILE_SHARE_READ,
                         NULL,
                         OPEN_EXISTING,
                         FILE_ATTRIBUTE_NORMAL,
                         NULL
                         );
    if(Handle == INVALID_HANDLE_VALUE)
    {
        DEBUG_PRINT("Invalid file Handle");
        return 0;
    }
    FileSize = GetFileSize(Handle, NULL);
    if(FileSize == INVALID_FILE_SIZE)
    {
        DEBUG_PRINT("Invalid file size");
        CloseHandle(Handle);
        return 0;
    }
    
    ASSERT_DEBUG(BufferSize > FileSize);
    DWORD NumberOfBytesRead = 0;
    DWORD TotalNumberOfBytesRead = 0;
    while(TotalNumberOfBytesRead < FileSize)
    {
        BOOL Result =  ReadFile(
                                Handle,
                                (LPVOID)Buffer,
                                FileSize,
                                &NumberOfBytesRead,
                                NULL
                                );
        if(Result == FALSE)
        {
            CloseHandle(Handle);
            return 0;
        }
        TotalNumberOfBytesRead += NumberOfBytesRead;
    }
    if(NullTerminate)
    {
        Buffer[TotalNumberOfBytesRead] = 0;
    }
    ASSERT_DEBUG(TotalNumberOfBytesRead == FileSize);
    CloseHandle(Handle);
    return TotalNumberOfBytesRead;
}

void Win32WriteFile(const char* FileName, u8* Buffer, u32 BufferSize)
{
    HANDLE Handle;
    u32 FileSize;
    Handle = CreateFileA(
                         FileName,
                         GENERIC_WRITE,
                         FILE_SHARE_READ | FILE_SHARE_WRITE,
                         NULL,
                         CREATE_ALWAYS,
                         FILE_ATTRIBUTE_NORMAL,
                         NULL
                         );
    if(Handle == INVALID_HANDLE_VALUE)
    {
        DEBUG_PRINT("Invalid file handle");
    }
    else
    {
        WriteFile(
                  Handle,
                  Buffer,
                  BufferSize,
                  NULL,
                  NULL
                  );
        CloseHandle(Handle);
    }
}