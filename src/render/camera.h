#ifndef CAMERA_H
#define CAMERA_H

#define GRAVITY 13.5f
#define AIR_RESISTENCE 0.5f
#define CROUCH_RESISTENCE 5.f
#define ACCELERATION 1.0f
#define MAX_SPEED 1.f

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "core/debug.h"

enum class CameraMovement
{
    RunForward,
    Forward,
    Backward,
    Left,
    Right,
    Jump,
    Crouch,
};

class Camera
{
public:
    Camera();
    ~Camera();

    void init();

    glm::mat4 getView() const;
    glm::mat4 getProjection() const;

    void setAspect(float aspect);

    // input
    void processKeyboard(CameraMovement direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    // per-frame physics/update (gravity, apply velocity)
    void update(float deltaTime);

    glm::vec3 getPosition() const { return m_position; }

    glm::vec3 m_position;
    glm::vec3 m_lookat;
    glm::vec3 m_up;
    glm::vec3 m_front;
    glm::vec3 m_right;

    float m_fov;
    float m_aspect;
    float m_near;
    float m_far;

    float m_yaw;
    float m_pitch;
    float m_movementSpeed;
    float m_mouseSensitivity;

    // physics
    float m_jumpVelority;
    float m_crouchVelority;
    float m_accelerated;
    bool m_grounded;
    bool m_crouched;
    float m_standHeight;
    float m_crouchHeight;

private:
    void screenShake(bool grounded, bool crouched);
};

#endif