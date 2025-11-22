#include "game.h"
#include "..\transform.cpp"
inline 
void InitEntity(game_entity* Entity,
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
void InitializeEntities(game_state* GameState)
{
    
    game_entity* Board = GameState->Items;
    game_entity* Card = GameState->Items + 1;
    game_entity* Card2 = GameState->Items + 2;
    game_entity* Card3 = GameState->Items + 3;
    
    f32 StartX = -5;
    InitEntity(Board, glm::vec3(0), glm::vec3(20,.1,10), GameState->BoardTexture, GameState->Cube);
    InitEntity(Card, glm::vec3(StartX,.1, 0), glm::vec3(2,.01,3), GameState->CardFindTexture, GameState->Cube);
    StartX += 5;
    InitEntity(Card2, glm::vec3(StartX,.1, 0), glm::vec3(2,.01,3), GameState->CardFindTexture, GameState->Cube);
    StartX += 5;
    InitEntity(Card3, glm::vec3(StartX,.1, 0), glm::vec3(2,.01,3), GameState->CardFindTexture, GameState->Cube);
    
    GameState->NumberOfItems = 4;
    
}

DLL_API Game_Update(GameUpdate)
{
    game_state* GameState = (game_state*)Memory;
    if(!GameState->IsInitialized)
    {
        GameState->BoardTexture = Api->LoadTexture("../assets/textures/wood.png", 4, false);
        GameState->CardFindTexture = Api->LoadTexture("../assets/textures/cardback.png", 4, true);
        GameState->Cube = Api->LoadCube();
        
        InitializeEntities(GameState);
        
        GameState->IsInitialized = true;
    }
    
    if(GameState->IsReloaded)
    {
        InitializeEntities(GameState);
        GameState->IsReloaded = false;
    }
    
}