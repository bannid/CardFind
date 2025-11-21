/* date = November 22nd 2025 8:38 am */

#ifndef GAME_H
#define GAME_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "..\types.h"

#define DLL_API extern "C" __declspec(dllexport)

#define Game_Update(Name) void Name(f32 DeltaTime, glm::vec3* Colour)
Game_Update(GameUpdateStub){}

typedef Game_Update(game_update);

#endif //GAME_H
