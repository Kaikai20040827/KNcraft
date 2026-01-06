#ifndef CAMERA_H
#define CAMERA_H

#define GRAVITY 13.5f
#define AIR_RESISTENCE 0.5f
#define CROUCH_RESISTENCE 5.f
#define ACCELERATION 1.0f
#define MAX_SPEED 1.f

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "core/debug/debug.h"

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

    glm::vec3 getPosition() const { return m_Position; }

    glm::vec3 m_Position;
    glm::vec3 m_Lookat;
    glm::vec3 m_Up;
    glm::vec3 m_Front;
    glm::vec3 m_Right;

    float m_Fov;
    float m_Aspect;
    float m_Near;
    float m_Far;

    float m_Yaw;
    float m_Pitch;
    float m_MovementSpeed;
    float m_MouseSensitivity;

    // physics
    float m_JumpVelority;
    float m_CrouchVelority;
    float m_Accelerated;
    bool m_Grounded;
    bool m_Crouched;
    float m_StandHeight;
    float m_CrouchHeight;

private:
    void screenShake(bool grounded, bool crouched);
};

#endif