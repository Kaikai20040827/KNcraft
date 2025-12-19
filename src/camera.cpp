#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

Camera::Camera()
    : position(0.f, 0.f, 3.f),
      front(0.f, 0.f, -1.f),
      up(0.f, 1.f, 0.f),
      yaw(-90.f),
      pitch(0.f),
      sensitivity(0.1f) {}

void Camera::processMouse(float deltaX, float deltaY)
{
    yaw += deltaX;
    pitch += deltaY;

    pitch = glm::clamp(pitch, -89.f, 89.f);

    glm::vec3 f;
    f.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    f.y = sin(glm::radians(pitch));
    f.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(f);
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(position, position + front, up);
}

void Camera::processKeyboard(
    float dt, bool w, bool s, bool a, bool d, bool space, bool shift)
{

    float speed = 3.0f * dt;
    glm::vec3 right = glm::normalize(glm::cross(front, up));

    if (w)
        position += speed * front;
    if (s)
        position -= speed * front;
    if (a)
        position -= speed * right;
    if (d)
        position += speed * right;
    if (space)
        position += speed * up;
    if (shift)
        position -= speed * up;
}
