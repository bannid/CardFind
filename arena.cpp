void* GetMemory(memory_arena* Arena, u32 Size)
{
    ARENA_IS_VALID(*Arena);
    ARENA_HAS_MEMORY(*Arena, Size);
    u8* Pointer = ((u8*)Arena->BasePointer) + Arena->Offset;
    Arena->Offset += Size;
    return ((void*)Pointer);
}

memory_arena GetMemoryArena(memory_arena* ArenaIn, u32 Size)
{
    memory_arena Arena = {};
    Arena.BasePointer = GetMemory(ArenaIn, Size);
    Arena.Offset = 0;
    Arena.Size = Size;
    Arena.Freed = false;
    Arena.Initialized = true;
    return Arena;
}

void ResetArena(memory_arena* Arena)
{
    ARENA_IS_VALID(*Arena);
    Arena->Offset = 0;
}