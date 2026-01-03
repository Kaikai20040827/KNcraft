#include "render/camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::init()
{
    m_position = glm::vec3{0.f, 1.8f, 2.6f};
    m_front = glm::vec3{0.f, 0.f, -1.f};
    m_up = glm::vec3{0.f, 1.f, 0.f};
    m_right = glm::normalize(glm::cross(m_front, m_up));

    m_fov = glm::radians(45.f);
    m_aspect = 1280.f / 800.f;
    m_near = 0.1f;
    m_far = 100.f;

    m_yaw = -90.f;
    m_pitch = 0.f;

    m_movementSpeed = 3.5f;
    m_mouseSensitivity = 0.1f;

    m_jumpVelority = 0.f;
    m_grounded = true;
    m_accelerated = false;
    m_crouched = false;
    m_standHeight = 1.8f;
    m_crouchHeight = 1.0f;
}

glm::mat4 Camera::getView() const
{
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 Camera::getProjection() const
{
    return glm::perspective(m_fov, m_aspect, m_near, m_far);
}

void Camera::setAspect(float a)
{
    m_aspect = a;
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime)
{
    float m_Velocity = m_movementSpeed * deltaTime;
    glm::vec3 flatFront = glm::normalize(glm::vec3(m_front.x, 0.0f, m_front.z));
    if (direction == CameraMovement::RunForward)
    {
        m_movementSpeed = 5.5f;
        m_position += flatFront * m_Velocity;
    }
    if (direction == CameraMovement::Forward)
    {
        m_movementSpeed = 3.5f;
        m_position += flatFront * m_Velocity;
    }
    if (direction == CameraMovement::Backward)
    {
        m_movementSpeed = 3.5f;
        m_position -= flatFront * m_Velocity;
    }
    if (direction == CameraMovement::Left)
    {
        m_movementSpeed = 3.5f;
        m_position -= m_right * m_Velocity;
    }
    if (direction == CameraMovement::Right)
    {
        m_movementSpeed = 3.5f;
        m_position += m_right * m_Velocity;
    }
    if (direction == CameraMovement::Jump)
    {
        if (m_grounded)
        {
            m_jumpVelority = 5.0f; // jump impulse
            m_grounded = false;
        }
    }
    if (direction == CameraMovement::Crouch)
    {
        m_movementSpeed = 1.5f;
        m_crouchVelority = 7.f;
        m_crouched = true;
    }
}

void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= m_mouseSensitivity;
    yoffset *= m_mouseSensitivity;

    m_yaw += xoffset;
    m_pitch += yoffset;

    if (constrainPitch)
    {
        if (m_pitch > 89.0f)
            m_pitch = 89.0f;
        if (m_pitch < -89.0f)
            m_pitch = -89.0f;
    }

    glm::vec3 f;
    f.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    f.y = sin(glm::radians(m_pitch));
    f.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(f);
    m_right = glm::normalize(glm::cross(m_front, m_up));
}

void Camera::update(float deltaTime)
{
    // apply gravity
    if (!m_grounded)
    {
        m_jumpVelority -= GRAVITY * deltaTime;
        m_position.y += m_jumpVelority * deltaTime;
        if (m_position.y <= (m_crouched ? m_crouchHeight : m_standHeight))
        {
            m_position.y = (m_crouched ? m_crouchHeight : m_standHeight);
            m_jumpVelority = 0.f;
            m_grounded = true;
        }
    }
    else
    {
        if (m_crouched)
        {
            m_crouchVelority -= CROUCH_RESISTENCE * deltaTime;
            m_position.y -= m_crouchVelority * deltaTime;
            if (m_position.y <= m_crouchHeight)
            {
                m_position.y = m_crouchHeight;
                m_crouchVelority = 0.f;
                m_grounded = true;
            }
        }
        else
        {
            m_position.y = m_standHeight;
        }
    }
    // reset crouch state each frame; app will set CROUCH when key pressed
    m_crouched = false;
}

void Camera::screenShake(bool grounded, bool crouched)
{
}