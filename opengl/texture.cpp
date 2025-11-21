u32 
LoadTexture(const char* FilePath, int32 DesiredChannels, b32 Flip)
{
    stbi_set_flip_vertically_on_load(Flip);
    int32 ActualChannels = DesiredChannels;
    u32 ID;
    int32 Width, Height;
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    uchar* Data = stbi_load(FilePath,
                            &Width,
                            &Height, 
                            &ActualChannels, 0);
    int Channels = ActualChannels == 4 ? GL_RGBA : GL_RGB;
    if (Data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, Channels,
                     Width, Height, 0, Channels,
                     GL_UNSIGNED_BYTE, Data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(Data);
        return ID;
    }
    return -1;
}