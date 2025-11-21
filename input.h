/* date = October 25th 2025 8:08 am */

#ifndef INPUT_H
#define INPUT_H

struct button_state
{
    b32                                              IsDown;
    b32                                              HeldDown;
    b32                                              IsReleased;
    b32                                              JustWentDown;
};

struct mouse_input
{
    v2                                               Position;
    button_state                                     Left;
    button_state                                     Right;
    f32                                              ScrollYOffset;
    v2                                               Offset;
};

struct keyboard_input
{
    button_state                                     Up;
    button_state                                     Down;
    button_state                                     Left;
    button_state                                     Right;
    button_state                                     Space;
    button_state                                     Escape;
    button_state                                     Ctrl;
};

struct input
{
    mouse_input                                      Mouse;
    keyboard_input                                   Keyboard;
};


#endif //INPUT_H
