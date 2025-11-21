#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include <glad.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glad.c"
#include "types.h"
#include "debug.h"
#include "utils.h"
#include "arena.h"
#include "game/game.h"

#include "win32/win32_file.h"
#include "win32/win32_dll.h"
#include "win32/win32_memory.h"
#include "opengl/shader.h"
#include "opengl/model.h"
#include "opengl/texture.h"
#include "transform.h"
#include "input.h"
#include "orbital_camera.h"

#include "utils.cpp"
#include "print_utils.cpp"
#include "arena.cpp"
#include "win32/win32_file.cpp"
#include "win32/win32_dll.cpp"
#include "win32/win32_memory.cpp"
#include "opengl/shader.cpp"
#include "opengl/model.cpp"
#include "opengl/texture.cpp"

#include "transform.cpp"
#include "loaders/obj_loader.cpp"
#include "input.cpp"
#include "orbital_camera.cpp"

#define ASSERT_DEBUG(expression) if(!(expression)) *((int*)0)=0


// NOTE(Banni): Input
global input Global_Input;

GLFWwindow* 
InitializeWindow(int32 Width, int32 Height, const char* WindowTitle)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    
    GLFWwindow* Window = glfwCreateWindow(Width,
                                          Height,
                                          WindowTitle,
                                          NULL,
                                          NULL);
    if (Window == NULL)
        return NULL;
    glfwMakeContextCurrent(Window);
    
    // glfwSwapInterval(1);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        return NULL;
    
    // NOTE(Banni): GL Flags
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glEnable(GL_BLEND);
    glEnable(GL_MULTISAMPLE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    return Window;
}

void GlfwScrollCallback(GLFWwindow *Window, real64 XOffset, real64 YOffset)
{
    Global_Input.Mouse.ScrollYOffset = YOffset;
}

struct ray
{
    glm::vec3 Origin;
    glm::vec3 Direction;
};

ray
GetRay(glm::vec2 MousePosition,
       glm::vec2 ScreenDimensions,
       glm::mat4 *Projection,
       glm::mat4 *View,
       glm::vec3 CameraPosition)
{
    f32 x = (2.0f * MousePosition.x) / ScreenDimensions.x - 1.0f;
    f32 y = (2.0f * MousePosition.y) / ScreenDimensions.y - 1.0f;
    
    glm::vec4 RayClip = glm::vec4(x, y, -1.0f, 1.0f);
    glm::vec4 RayEye = glm::inverse(*Projection) * RayClip;
    RayEye.z = -1.0f;
    RayEye.w = 0.0f;
    
    glm::vec3 RayWorld = glm::normalize(glm::vec3(glm::inverse(*View) * RayEye));
    
    ray Result;
    Result.Origin = CameraPosition;
    Result.Direction = RayWorld;
    return (Result);
    
}

global int32 Global_Width;
global int32 Global_Height;
global b32   Global_Resized;

void FrameBufferResizeCallback(GLFWwindow *Window, int32 Width, int32 Height)
{
    glViewport(0, 0, Width, Height);
    Global_Width = Width;
    Global_Height = Height;
    Global_Resized = true;
}

struct entity
{
    transform Transform;
    u32 TextureID;
    gl_model Model;
};

inline 
void InitEntity(entity* Entity,
                glm::vec3 Position,
                glm::vec3 Scale,
                u32 TextureID,
                gl_model Model)
{
    InitTransform(&Entity->Transform);
    Entity->Transform.Position = Position;
    Entity->Transform.Scale = Scale;
    Entity->TextureID = TextureID;
    Entity->Model = Model;
}

inline
void DrawEntity(entity* Entity, gl_shader_program Shader)
{
    
    glm::mat4 ModelMat;
    ModelMat = TransformToMat4(&Entity->Transform);
    glm::vec3 White = glm::vec3(1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Entity->TextureID);
    GL_DrawModel(&Entity->Model, &Shader, (f32*)&ModelMat, (f32*)&White);
}

int32 CALLBACK WinMain(HINSTANCE instance,
                       HINSTANCE prevInstance,
                       LPSTR commandLine,
                       int showCode)
{
    memory_arena MainArena = Win32GetMemoryArena(MEGABYTE(50));
    memory_arena ScratchArena = GetMemoryArena(&MainArena, MEGABYTE(10));
    Global_Width = 800;
    Global_Height = 800;
    GLFWwindow* Window = InitializeWindow(Global_Width, Global_Height, "Card find");
    ASSERT_DEBUG(Window != NULL);
    glfwSetFramebufferSizeCallback(Window, FrameBufferResizeCallback);
    glm::mat4 ProjectionMat = glm::perspective(glm::radians(50.0f),
                                               (f32)Global_Width / Global_Height,
                                               .1f,
                                               500.0f);
    gl_model Cube = GL_LoadCubeToGPU();
    u32 BoardTexture = LoadTexture("../assets/textures/wood.png", 4, false);
    u32 CardFindTexture = LoadTexture("../assets/textures/cardback.png", 4, true);
    gl_shader_program MainShader = GL_LoadShaderFromFile("../shaders/main.vs.c",
                                                         "../shaders/main.fs.c",
                                                         ScratchArena);
    
    // NOTE(Banni): Camera
    orbital_camera Camera;
    InitiateOrbitalCamera(&Camera, glm::vec3(0), 30.0f);
    Camera.Orientation = glm::angleAxis(glm::radians(-20.0f), glm::vec3(1,0,0));
    glm::mat4 ViewMat;
    
    // NOTE(Banni): Timings
    f32 CurrentTime = glfwGetTime();
    f32 LastTime = CurrentTime;
    
    // NOTE(Banni): Input callbacks
    glfwSetScrollCallback(Window, GlfwScrollCallback);
    
    entity Board;
    InitEntity(&Board, glm::vec3(0), glm::vec3(20,.1,10), BoardTexture, Cube);
    
    entity Card;
    InitEntity(&Card, glm::vec3(0,.1, 0), glm::vec3(2,.01,3), CardFindTexture, Cube);
    
    win32_game_code GameCode = Win32LoadGameDLL(false);
    
    while(!glfwWindowShouldClose(Window))
    {
        FILETIME NewDllWriteTime = Win32GetLastWriteTime(GAME_DLL_NAME);
        if (CompareFileTime(&NewDllWriteTime, &GameCode.LastWriteTime) != 0)
        {
            Win32UnloadGameDLL(&GameCode);
            GameCode = Win32LoadGameDLL(true);
        }
        
        // NOTE(Banni): Timings update
        CurrentTime = glfwGetTime();
        f32 DeltaTime = CurrentTime - LastTime;
        
        LastTime = CurrentTime;
        
        // NOTE(Banni): Update input
        GlfwProcessInput(Window, &Global_Input);
        
        // NOTE(Banni): Update the camera
        Update(&Camera, &Global_Input, DeltaTime);
        
        glm::vec3 FromGameDll;
        GameCode.GameUpdate(DeltaTime, &FromGameDll);
        
        if(Global_Resized)
        {
            ProjectionMat = glm::perspective(glm::radians(50.0f),
                                             (f32)Global_Width / Global_Height,
                                             .1f,
                                             500.0f);
            Global_Resized = false;
        }
        
        ViewMat = GetViewMatrix(&Camera);
        glm::vec3 CameraPosition = GetPosition(&Camera);
        ray Ray = GetRay(Global_Input.Mouse.Position,
                         glm::vec2(Global_Width, Global_Height),
                         &ProjectionMat,
                         &ViewMat,
                         CameraPosition);
        
        // NOTE(Banni): Render
        glClearColor(0,0,0,0);
        glClearColor(FromGameDll.x, FromGameDll.y, FromGameDll.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(MainShader.ID);
        glUniformMatrix4fv(MainShader.ProjectionLocation,
                           1,
                           GL_FALSE,
                           (f32*)&ProjectionMat);
        
        glUniformMatrix4fv(MainShader.ViewLocation,
                           1,
                           GL_FALSE,
                           (f32*)&ViewMat);
        DrawEntity(&Board, MainShader);
        DrawEntity(&Card, MainShader);
        // NOTE(Banni): Clear mouse's scroll values
        Global_Input.Mouse.ScrollYOffset = 0;
        
        glfwSwapBuffers(Window);
        glfwPollEvents();
    }
    return 0;
}