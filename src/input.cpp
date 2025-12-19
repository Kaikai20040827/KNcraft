#include "input.h"

InputManager::InputManager()
    : lastX(0.0f), lastY(0.0f), firstMouse(true),
      deltaX(0.0f), deltaY(0.0f), sensitivity(0.1f) {}

void InputManager::processKeyboard(GLFWwindow *window, float deltaTime,
                                   bool &w, bool &s, bool &a, bool &d,
                                   bool &space, bool &shift) const
{
    w = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
    s = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
    a = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
    d = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
    space = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
    shift = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
            glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS;
}

void InputManager::processMouse(double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = static_cast<float>(xpos);
        lastY = static_cast<float>(ypos);
        firstMouse = false;
    }

    deltaX = static_cast<float>(xpos) - lastX;
    deltaY = lastY - static_cast<float>(ypos); // reversed: y ranges bottom->top

    lastX = static_cast<float>(xpos);
    lastY = static_cast<float>(ypos);

    deltaX *= sensitivity;
    deltaY *= sensitivity;
}

bool InputManager::isKeyPressed(GLFWwindow *window, int key) const
{
    return glfwGetKey(window, key) == GLFW_PRESS;
}

glm::vec2 InputManager::getMouseDelta() const
{
    return glm::vec2(deltaX, deltaY);
}

void InputManager::resetMouseDelta()
{
    deltaX = 0.0f;
    deltaY = 0.0f;
}