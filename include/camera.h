#ifndef CAMERA_H
#define CAMERA_H

#define GRAVITY 13.5f
#define AIR_RESISTENCE 0.5f
#define CROUCH_RESISTENCE 5.f
#define ACCELERATION 1.0f
#define MAX_SPEED 1.f

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "debug.h"

enum CameraMovement
{   
    RUN_FORWARD,
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    JUMP,
    CROUCH,
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

    glm::vec3 getPosition() const { return position; }

    glm::vec3 position;
    glm::vec3 lookat;
    glm::vec3 up;
    glm::vec3 front;
    glm::vec3 right;

    float fov;
    float aspect;
    float near;
    float far;

    float yaw;
    float pitch;
    float movementSpeed;
    float mouseSensitivity;

    // physics
    float jumpVelority;
    float crouchVelority;
    float accelerated;
    bool grounded;
    bool crouched;
    float standHeight;
    float crouchHeight;

};

#endif