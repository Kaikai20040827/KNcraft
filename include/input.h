#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class InputManager
{
public:
    InputManager();

    void processKeyboard(GLFWwindow *window, float deltaTime,
                         bool &w, bool &s, bool &a, bool &d,
                         bool &space, bool &shift) const;

    void processMouse(double xpos, double ypos);

    bool isKeyPressed(GLFWwindow *window, int key) const;

    glm::vec2 getMouseDelta() const;

    void resetMouseDelta();

private:
    float lastX, lastY;
    bool firstMouse;
    float deltaX, deltaY;
    float sensitivity;
};

#endif