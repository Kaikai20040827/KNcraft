#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>

class Camera
{
public:
    Camera();

    void processKeyboard(float deltaTime, bool w, bool s, bool a, bool d, bool space, bool shift);
    void processMouse(float deltaX, float deltaY);

    glm::mat4 getViewMatrix() const;

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;

private:
    float yaw;
    float pitch;
    float sensitivity;
};

#endif