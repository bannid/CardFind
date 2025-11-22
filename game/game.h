/* date = November 22nd 2025 8:38 am */

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "..\types.h"
#include "..\utils.h"
#include "..\transform.h"
#include "..\opengl/shader.h"
#include "..\opengl/model.h"
#include "..\opengl/texture.h"
#include "game_entity.h"

#define DLL_API extern "C" __declspec(dllexport)

#define Graphics_Api_Load_Texture(Name) u32 Name(const char* Path, int32 DesiredChannels, b32 flip)
typedef Graphics_Api_Load_Texture(gapi_load_texture);

#define Graphics_Api_Load_Model(Name) gl_model Name(const char* Path)
typedef Graphics_Api_Load_Model(gapi_load_model);

#define Graphics_Api_Load_Shape(Name) gl_model Name()
typedef Graphics_Api_Load_Shape(load_cube);

struct graphics_api
{
    gapi_load_texture*            LoadTexture;
    gapi_load_model*              LoadModel;
    load_cube*                    LoadCube;
};


struct game_state
{
    std::vector<game_entity> Items;
    game_entity Board;
    
    game_entity CardOne;
    game_entity CardTwo;
    game_entity CardThree;
    
    b32 IsInitialized;
    b32 IsReloaded;
};


#define Game_Update(Name) void Name(void* Memory, graphics_api* Api, f32 DeltaTime)
Game_Update(GameUpdateStub){}

typedef Game_Update(game_update);

#endif //GAME_H
