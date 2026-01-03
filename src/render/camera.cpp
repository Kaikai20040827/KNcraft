#include "render/camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::init()
{
    m_Position = glm::vec3{0.f, 1.8f, 2.6f};
    m_Front = glm::vec3{0.f, 0.f, -1.f};
    m_Up = glm::vec3{0.f, 1.f, 0.f};
    m_Right = glm::normalize(glm::cross(m_Front, m_Up));

    m_Fov = glm::radians(45.f);
    m_Aspect = 1280.f / 800.f;
    m_Near = 0.1f;
    m_Far = 100.f;

    m_Yaw = -90.f;
    m_Pitch = 0.f;

    m_MovementSpeed = 3.5f;
    m_MouseSensitivity = 0.1f;

    m_JumpVelority = 0.f;
    m_Grounded = true;
    m_Accelerated = false;
    m_Crouched = false;
    m_StandHeight = 1.8f;
    m_CrouchHeight = 1.0f;
}

glm::mat4 Camera::getView() const
{
    return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

glm::mat4 Camera::getProjection() const
{
    return glm::perspective(m_Fov, m_Aspect, m_Near, m_Far);
}

void Camera::setAspect(float a)
{
    m_Aspect = a;
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime)
{
    float m_Velocity = m_MovementSpeed * deltaTime;
    glm::vec3 flatFront = glm::normalize(glm::vec3(m_Front.x, 0.0f, m_Front.z));
    if (direction == CameraMovement::RunForward)
    {
        m_MovementSpeed = 5.5f;
        m_Position += flatFront * m_Velocity;
    }
    if (direction == CameraMovement::Forward)
    {
        m_MovementSpeed = 3.5f;
        m_Position += flatFront * m_Velocity;
    }
    if (direction == CameraMovement::Backward)
    {
        m_MovementSpeed = 3.5f;
        m_Position -= flatFront * m_Velocity;
    }
    if (direction == CameraMovement::Left)
    {
        m_MovementSpeed = 3.5f;
        m_Position -= m_Right * m_Velocity;
    }
    if (direction == CameraMovement::Right)
    {
        m_MovementSpeed = 3.5f;
        m_Position += m_Right * m_Velocity;
    }
    if (direction == CameraMovement::Jump)
    {
        if (m_Grounded)
        {
            m_JumpVelority = 5.0f; // jump impulse
            m_Grounded = false;
        }
    }
    if (direction == CameraMovement::Crouch)
    {
        m_MovementSpeed = 1.5f;
        m_CrouchVelority = 7.f;
        m_Crouched = true;
    }
}

void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= m_MouseSensitivity;
    yoffset *= m_MouseSensitivity;

    m_Yaw += xoffset;
    m_Pitch += yoffset;

    if (constrainPitch)
    {
        if (m_Pitch > 89.0f)
            m_Pitch = 89.0f;
        if (m_Pitch < -89.0f)
            m_Pitch = -89.0f;
    }

    glm::vec3 f;
    f.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    f.y = sin(glm::radians(m_Pitch));
    f.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Front = glm::normalize(f);
    m_Right = glm::normalize(glm::cross(m_Front, m_Up));
}

void Camera::update(float deltaTime)
{
    // apply gravity
    if (!m_Grounded)
    {
        m_JumpVelority -= GRAVITY * deltaTime;
        m_Position.y += m_JumpVelority * deltaTime;
        if (m_Position.y <= (m_Crouched ? m_CrouchHeight : m_StandHeight))
        {
            m_Position.y = (m_Crouched ? m_CrouchHeight : m_StandHeight);
            m_JumpVelority = 0.f;
            m_Grounded = true;
        }
    }
    else
    {
        if (m_Crouched)
        {
            m_CrouchVelority -= CROUCH_RESISTENCE * deltaTime;
            m_Position.y -= m_CrouchVelority * deltaTime;
            if (m_Position.y <= m_CrouchHeight)
            {
                m_Position.y = m_CrouchHeight;
                m_CrouchVelority = 0.f;
                m_Grounded = true;
            }
        }
        else
        {
            m_Position.y = m_StandHeight;
        }
    }
    // reset crouch state each frame; app will set CROUCH when key pressed
    m_Crouched = false;
}

void Camera::screenShake(bool grounded, bool crouched)
{
}