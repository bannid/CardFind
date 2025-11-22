/* date = November 22nd 2025 0:12 pm */

#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

struct game_entity
{
    transform Transform;
    u32 TextureID;
    gl_model Model;
};

#endif //GAME_ENTITY_H
