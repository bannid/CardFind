inline 
void CopyString(char* Source, char* Destination, u32 MaxLength, u32 Length)
{
    ASSERT_DEBUG(Length < MaxLength);
    for(int32 i = 0; i < Length; i++)
    {
        Destination[i] = Source[i];
    }
    Destination[Length] = 0;
}