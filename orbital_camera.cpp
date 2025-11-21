inline void
InitiateOrbitalCamera(orbital_camera *Camera, glm::vec3 Target, f32 Radius)
{
    Camera->Target = Target;
    Camera->Radius = Radius;
}

glm::mat4 GetViewMatrix(orbital_camera *Camera)
{
    glm::vec3 Forward = Camera->Orientation * glm::vec3(0,0,-1);
    glm::vec3 Position = Camera->Target - Forward * Camera->Radius;
    glm::vec3 Up = Camera->Orientation * glm::vec3(0,1,0);
    return glm::lookAt(Position, Camera->Target, Up);
}

glm::vec3 GetPosition(orbital_camera *Camera)
{
    glm::vec3 Forward = Camera->Orientation * glm::vec3(0,0,-1);
    glm::vec3 Result = Camera->Target - Forward * Camera->Radius;
    
    return (Result);
}

inline void
Update(orbital_camera *Camera,
       input *Input,
       f32 DeltaTime)
{
    float ScrollSpeed = 1.0f;
    if (Input->Keyboard.Ctrl.IsDown)
    {
        ScrollSpeed = 5.0f;
    }
    // NOTE(Banni): Process the input
    Camera->Radius -= Input->Mouse.ScrollYOffset * ScrollSpeed;
    Camera->Radius = MAX(10.0f, Camera->Radius);
    
    // NOTE(Banni): Rotate the camera 
    if(Input->Mouse.Right.IsDown)
    {
        f32 Speed = 20.0f;
        f32 x = Input->Mouse.Offset.x;
        f32 y = Input->Mouse.Offset.y;
        
        glm::quat Rotation = glm::angleAxis(glm::radians(x * -Speed) * DeltaTime, glm::vec3(0,1,0));
        Camera->Orientation = Rotation * Camera->Orientation;
        
        glm::vec3 Right = Camera->Orientation * glm::vec3(1,0,0);
        Rotation = glm::angleAxis(glm::radians(-Speed * y) * DeltaTime, Right);
        Camera->Orientation = Rotation * Camera->Orientation;
    }
    
}