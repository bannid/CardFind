
struct token
{
    char* Token;
    u32 Length;
};

struct tokenizer
{
    char* At;
};

b32 IsWhiteSpace(char* Token)
{
    return(*Token == '\n' ||
           *Token == '\t' ||
           *Token == '\r' ||
           *Token == ' '); 
}

void EatWhiteSpace(tokenizer* Tokenizer)
{
    while(IsWhiteSpace(Tokenizer->At))
    {
        if(*Tokenizer->At == 0) break;
        Tokenizer->At++;
    }
}

token GetNextToken(tokenizer* Tokenizer)
{
    EatWhiteSpace(Tokenizer);
    token Result = {};
    Result.Token = Tokenizer->At;
    while(!IsWhiteSpace(Tokenizer->At))
    {
        if(Tokenizer->At == 0) break;
        Tokenizer->At++;
        Result.Length++;
    }
    return Result;
}

void EatLine(tokenizer* Tokenizer)
{
    while(*Tokenizer->At != '\n')
    {
        if(*Tokenizer->At == 0) break;
        Tokenizer->At++;
    }
}

token ReadUntilChar(tokenizer* Tokenizer, char c)
{
    token Result = {};
    Result.Token = Tokenizer->At;
    while(*Tokenizer->At != c)
    {
        if(*Tokenizer->At == 0) break;
        Tokenizer->At++;
        Result.Length++;
    }
    if(*Tokenizer->At == c) Tokenizer->At++;
    return Result;
}

UsesScratchArena
gl_model LoadObjModelToGPU(const char* ModelPath, memory_arena ScratchArena)
{
    const u32 MAX_VERTICES = 1000;
    const u32 MAX_NORMALS = 1000;
    const u32 MAX_UVS = 1000;
    const u32 MAX_FACES = 1000;
    
    glm::vec3* Vertices = (glm::vec3*)GetMemory(&ScratchArena, sizeof(glm::vec3) * MAX_VERTICES);
    glm::vec3* Normals = (glm::vec3*)GetMemory(&ScratchArena, sizeof(glm::vec3) * MAX_NORMALS);
    gl_vertex* Vertexes = (gl_vertex*)GetMemory(&ScratchArena, sizeof(gl_vertex) * MAX_FACES);
    u8* FileBuffer = (u8*)GetMemory(&ScratchArena, MEGABYTE(2));
    
    u32 NumberOfVertices = 0;
    u32 NumberOfNormals = 0;
    u32 NumberOfVertexes = 0;
    u32 BytesRead = Win32ReadEntireFileV2(ModelPath, FileBuffer, MEGABYTE(2), true);
    
    tokenizer Tokenizer = {(char*)FileBuffer};
    char FloatBuffer[32];
    char Int32Buffer[32];
    while(*Tokenizer.At != 0)
    {
        EatWhiteSpace(&Tokenizer);
        // NOTE(Banni): Parse vertice
        if(Tokenizer.At[0] == 'v' && Tokenizer.At[1] == ' ')
        {
            token Token = {};
            glm::vec3 Vertice = {};
            
            // NOTE(Banni): Skip the 'v'
            Tokenizer.At++;
            
            Token = GetNextToken(&Tokenizer);
            CopyString(Token.Token, FloatBuffer, ARRAY_COUNT(FloatBuffer), Token.Length);
            Vertice.x = atof(FloatBuffer);
            
            Token = GetNextToken(&Tokenizer);
            CopyString(Token.Token, FloatBuffer, ARRAY_COUNT(FloatBuffer), Token.Length);
            Vertice.y = atof(FloatBuffer);
            
            Token = GetNextToken(&Tokenizer);
            CopyString(Token.Token, FloatBuffer, ARRAY_COUNT(FloatBuffer), Token.Length);
            Vertice.z = atof(FloatBuffer);
            Vertices[NumberOfVertices++] = Vertice;
            ASSERT_DEBUG(NumberOfVertices <= MAX_VERTICES);
        }
        
        else if(Tokenizer.At[0] == 'v' && Tokenizer.At[1] == 'n' && Tokenizer.At[2] == ' ')
        {
            token Token = {};
            glm::vec3 Normal = {};
            
            // NOTE(Banni): Skip the 'vn'
            Tokenizer.At++;
            Tokenizer.At++;
            
            Token = GetNextToken(&Tokenizer);
            CopyString(Token.Token, FloatBuffer, ARRAY_COUNT(FloatBuffer), Token.Length);
            Normal.x = atof(FloatBuffer);
            
            Token = GetNextToken(&Tokenizer);
            CopyString(Token.Token, FloatBuffer, ARRAY_COUNT(FloatBuffer), Token.Length);
            Normal.y = atof(FloatBuffer);
            
            Token = GetNextToken(&Tokenizer);
            CopyString(Token.Token, FloatBuffer, ARRAY_COUNT(FloatBuffer), Token.Length);
            Normal.z = atof(FloatBuffer);
            Normals[NumberOfNormals++] = Normal;
            ASSERT_DEBUG(NumberOfNormals <= MAX_NORMALS);
        }
        
        else if(Tokenizer.At[0] == 'f' && Tokenizer.At[1] == ' ')
        {
            token Token = {};
            u32 VerticeIndex = 0;
            u32 NormalIndex = 0;
            u32 TextureIndex = 0;
            
            // NOTE(Banni): Skip the 'f'
            Tokenizer.At++;
            for(int i = 0; i < 3; i++)
            {
                EatWhiteSpace(&Tokenizer);
                Token = ReadUntilChar(&Tokenizer, '/');
                CopyString(Token.Token, Int32Buffer, ARRAY_COUNT(Int32Buffer), Token.Length);
                VerticeIndex = atoi(Int32Buffer);
                ASSERT_DEBUG(VerticeIndex <= NumberOfVertices);
                
                // NOTE(Banni): Read the uv
                Token = ReadUntilChar(&Tokenizer, '/');
                if(Token.Length)
                {
                    CopyString(Token.Token, Int32Buffer, ARRAY_COUNT(Int32Buffer), Token.Length);
                    TextureIndex = atoi(Int32Buffer);
                }
                
                char CharToMatch = i != 2 ? ' ' : '\n';
                
                // NOTE(Banni): Read the normal
                Token = ReadUntilChar(&Tokenizer, CharToMatch);
                if(Token.Length)
                {
                    CopyString(Token.Token, Int32Buffer, ARRAY_COUNT(Int32Buffer), Token.Length);
                    NormalIndex = atoi(Int32Buffer);
                    ASSERT_DEBUG(NormalIndex <= NumberOfNormals);
                }
                gl_vertex Vertex = {};
                Vertex.Normal = Normals[NormalIndex-1];
                Vertex.Position = Vertices[VerticeIndex - 1];
                Vertexes[NumberOfVertexes++] = Vertex;
            }
        }
        else
        {
            EatLine(&Tokenizer);
        }
    }
    gl_model Result = GL_LoadModelToGPU_VNU((f32*)Vertexes, sizeof(gl_vertex), NumberOfVertexes);
    
    return(Result);
}