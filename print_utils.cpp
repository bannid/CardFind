inline void
PrintFloat(f32 Value)
{
    char Buffer[32];
    snprintf(Buffer, ARRAY_COUNT(Buffer), "Value is: %f \n", Value);
    DEBUG_PRINT(Buffer);
}

inline void
PrintInt32(int32 Value)
{
    char Buffer[32];
    snprintf(Buffer, ARRAY_COUNT(Buffer), "Value is: %d \n", Value);
    DEBUG_PRINT(Buffer);
}