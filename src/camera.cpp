#include "camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::init()
{
    position = glm::vec3{0.f, 1.8f, 2.6f};
    front = glm::vec3{0.f, 0.f, -1.f};
    up = glm::vec3{0.f, 1.f, 0.f};
    right = glm::normalize(glm::cross(front, up));

    fov = glm::radians(45.f);
    aspect = 1280.f / 800.f;
    near = 0.1f;
    far = 100.f;

    yaw = -90.f;
    pitch = 0.f;

    movementSpeed = 3.5f;
    mouseSensitivity = 0.1f;

    jumpVelority = 0.f;
    crouchVelority = 0.f;
    grounded = true;
    accelerated = false;
    crouched = false;
    standHeight = 1.8f;
    crouchHeight = 1.0f;
}

glm::mat4 Camera::getView() const
{
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjection() const
{
    return glm::perspective(fov, aspect, near, far);
}

void Camera::setAspect(float a)
{
    aspect = a;
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime)
{

    float velocity = movementSpeed * deltaTime;
    glm::vec3 flatFront = glm::normalize(glm::vec3(front.x, 0.0f, front.z));
    if (direction == RUN_FORWARD)
    {
        movementSpeed = 5.5f;
        position += flatFront * velocity;
    }
    if (direction == FORWARD)
    {

        movementSpeed = 3.5f;
        position += flatFront * velocity;
    }
    if (direction == BACKWARD)
    {
        movementSpeed = 3.5f;
        position -= flatFront * velocity;
    }
    if (direction == LEFT)
    {
        movementSpeed = 3.5f;
        position -= right * velocity;
    }
    if (direction == RIGHT)
    {
        movementSpeed = 3.5f;
        position += right * velocity;
    }
    if (direction == JUMP)
    {
        
        if (grounded)
        {
            jumpVelority = 5.0f; // jump impulse
            grounded = false;
        }
        
    }
    if (direction == CROUCH)
    {
        movementSpeed = 1.5f;
        crouchVelority = 7.f;
        crouched = true;
    }
}

void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (constrainPitch)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    glm::vec3 f;
    f.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    f.y = sin(glm::radians(pitch));
    f.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(f);
    right = glm::normalize(glm::cross(front, up));
}

void Camera::update(float deltaTime)
{
    // apply gravity
    if (!grounded)
    {
        jumpVelority -= GRAVITY * deltaTime;
        position.y += jumpVelority * deltaTime;
        if (position.y <= (crouched ? crouchHeight : standHeight))
        {
            position.y = (crouched ? crouchHeight : standHeight);
            jumpVelority = 0.f;
            grounded = true;
        }
    }
    else
    {
        // if crouched, lower height
        if (crouched)
        {

            crouchVelority -= CROUCH_RESISTENCE * deltaTime;
            position.y -= crouchVelority * deltaTime;
            if (position.y <= crouchHeight)
            {
                position.y = crouchHeight;
                crouchVelority = 0.f;
                grounded = true;
            }
        }
        else
        {
            position.y = standHeight;
        }
    }
    // reset crouch state each frame; app will set CROUCH when key pressed
    crouched = false;
}

void Camera::screenShake(bool grounded, bool crouched) {
    
}