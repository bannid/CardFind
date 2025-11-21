/* date = October 19th 2025 10:53 am */

#ifndef SHADER_H
#define SHADER_H

struct gl_shader_program
{
    b32                 Valid;
    int32               ID;
    
    u32                 ProjectionLocation;
    u32                 ViewLocation;
    u32                 ModelLocation;
    u32                 ColourLocation;
};


#endif //SHADER_H
