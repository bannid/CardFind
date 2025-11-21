/* date = October 19th 2025 11:00 am */

#ifndef MODEL_H
#define MODEL_H

struct gl_vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 Uv;
};

struct gl_model
{
    u32 VaoID;
    u32 VboID;
    u32 VertCount;
};

#endif //MODEL_H
