#include "game.h"
#include "..\transform.cpp"

inline 
void InitEntity(game_entity* Entity,
                glm::vec3 Position,
                glm::vec3 Scale,
                game_entity_type Type)
{
    InitTransform(&Entity->Transform);
    Entity->Transform.Position = Position;
    Entity->Transform.Scale = Scale;
    Entity->Type = Type;
}

inline 
void InitializeEntities(game_state* GameState)
{
    
    f32 StartX = -5;
    InitEntity(&GameState->Board,
               glm::vec3(0,-.1,0),
               glm::vec3(20,.1,10),
               Game_Entity_Type_Board);
    
    InitEntity(&GameState->CardOne,
               glm::vec3(StartX,.1, 0),
               glm::vec3(2,.01,3),
               Game_Entity_Type_DummyCard);
    StartX += 5;
    
    InitEntity(&GameState->CardTwo,
               glm::vec3(StartX,.1, 0),
               glm::vec3(2,.01,3),
               Game_Entity_Type_DummyCard);
    StartX += 5;
    
    InitEntity(&GameState->CardThree,
               glm::vec3(StartX,.1, 0),
               glm::vec3(2,.01,3),
               Game_Entity_Type_TargetCard);
    
    GameState->CardThree.AnimationActive = true;
    GameState->CardThree.AnimationTime = 0.0f;
}

game_entity MoveUpAnimation(game_entity *Entity, f32 DeltaTime)
{
    if (!Entity->AnimationActive) return (*Entity);
    std::vector<f32> Frames;
    Frames.push_back(5.0f);
    Frames.push_back(15.0f);
    Frames.push_back(25.0f);
    Frames.push_back(0.0f);
    f32 NumberOfFrames = Frames.size();
    f32 AnimationTime = 2.0f;
    f32 TimePerPose = AnimationTime / NumberOfFrames;
    u32 CurrentPoseIndex = Entity->AnimationTime / TimePerPose;
    
    f32 Start;
    f32 Target = Frames[CurrentPoseIndex];
    
    if (CurrentPoseIndex == 0)
    {
        Start = Entity->Transform.Position.y;
    }
    else
    {
        Start = Frames[CurrentPoseIndex - 1];
    }
    
    f32 Percent = (Entity->AnimationTime - TimePerPose * CurrentPoseIndex) / TimePerPose;
    Percent = MIN(1.0f, Percent);
    game_entity Result = *Entity;
    Result.Transform.Position.y = (1.0f - Percent) * Start + Percent * Target;
    Entity->AnimationTime += DeltaTime;
    if (Entity->AnimationTime >= AnimationTime) 
    {
        Entity->AnimationTime = 0;
    }
    return (Result);
    
}

DLL_API Game_Update(GameUpdate)
{
    game_state* GameState = (game_state*)Memory;
    if(!GameState->IsInitialized)
    {
        InitializeEntities(GameState);
        GameState->IsInitialized = true;
    }
    
    if(GameState->IsReloaded)
    {
        InitializeEntities(GameState);
        GameState->IsReloaded = false;
    }
    GameState->Items.clear();
    GameState->Items.push_back(GameState->Board);
    GameState->Items.push_back(GameState->CardOne);
    GameState->Items.push_back(GameState->CardTwo);
    GameState->Items.push_back(MoveUpAnimation(&GameState->CardThree, DeltaTime));
}