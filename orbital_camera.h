/* date = October 25th 2025 8:00 am */

#ifndef ORBITAL_CAMERA_H
#define ORBITAL_CAMERA_H

struct orbital_camera
{
    glm::vec3 Target;
    f32 Radius;
    glm::quat Orientation;
};

#endif //ORBITAL_CAMERA_H
