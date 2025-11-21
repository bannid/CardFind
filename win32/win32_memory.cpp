memory_arena Win32GetMemoryArena(u32 Size)
{
    memory_arena Arena = {};
    Arena.BasePointer = Win32_Get_Memory(Size);
    Arena.Offset = 0;
    Arena.Size = Size;
    Arena.Freed = false;
    Arena.Initialized = true;
    return Arena;
}
