/* date = November 22nd 2025 0:12 pm */

#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

enum game_entity_type
{
    Game_Entity_Type_Board,
    Game_Entity_Type_DummyCard,
    Game_Entity_Type_TargetCard
};

struct game_entity
{
    transform Transform;
    game_entity_type Type;
    f32 AnimationTime;
    b32 AnimationActive;
};

#endif //GAME_ENTITY_H
