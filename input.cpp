inline void
GlfwCheckState(button_state *ButtonState,
               button_state LastState,
               int32 KeyState)
{
    ButtonState->IsDown = KeyState == GLFW_PRESS;
    ButtonState->HeldDown = KeyState == GLFW_REPEAT;
    ButtonState->IsReleased = KeyState == GLFW_RELEASE && LastState.IsDown;
    ButtonState->JustWentDown = ButtonState->IsDown && !LastState.IsDown;
}

inline void 
GlfwProcessInput(GLFWwindow *Window, input *Input)
{
    local_persist mouse_input LastFrameMouse;
    local_persist keyboard_input LastFrameKeyboard;
    
    // NOTE(Banni): Mouse input
    real64 x;
    real64 y;
    glfwGetCursorPos(Window, &x, &y);
    
    // TODO(Banni): Get the height of the window here somehow
    //y = GlobalRenderer.Height - y;
    
    Input->Mouse.Position = v2((f32)x, (f32)y);
    Input->Mouse.Offset = Input->Mouse.Position - LastFrameMouse.Position;
    GlfwCheckState(&Input->Mouse.Left,
                   LastFrameMouse.Left,
                   glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT));
    GlfwCheckState(&Input->Mouse.Right,
                   LastFrameMouse.Right,
                   glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_RIGHT));
    
    GlfwCheckState(&Input->Keyboard.Up,
                   LastFrameKeyboard.Up,
                   glfwGetKey(Window, GLFW_KEY_UP));
    GlfwCheckState(&Input->Keyboard.Down,
                   LastFrameKeyboard.Down,
                   glfwGetKey(Window, GLFW_KEY_DOWN));
    GlfwCheckState(&Input->Keyboard.Right,
                   LastFrameKeyboard.Right,
                   glfwGetKey(Window, GLFW_KEY_RIGHT));
    GlfwCheckState(&Input->Keyboard.Left,
                   LastFrameKeyboard.Left,
                   glfwGetKey(Window, GLFW_KEY_LEFT));
    GlfwCheckState(&Input->Keyboard.Space,
                   LastFrameKeyboard.Space,
                   glfwGetKey(Window, GLFW_KEY_SPACE));
    GlfwCheckState(&Input->Keyboard.Escape,
                   LastFrameKeyboard.Escape,
                   glfwGetKey(Window, GLFW_KEY_ESCAPE));
    GlfwCheckState(&Input->Keyboard.Ctrl,
                   LastFrameKeyboard.Ctrl,
                   glfwGetKey(Window, GLFW_KEY_LEFT_CONTROL));
    
    LastFrameMouse = Input->Mouse;
    LastFrameKeyboard = Input->Keyboard;
}
