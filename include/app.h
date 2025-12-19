#ifndef APP_H
#define APP_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "buffer.h"
#include "shader.h"
#include "vertex.h"

class Minecraft
{
public:
    void run();

private:
    // Basic run stages (called from run())
    void initWindow();
    void initBuffers();
    void initShaders();
    void mainloop();

    // helpers
    unsigned int compileShader(unsigned int type, const char *src);
    unsigned int createProgram(const char *vsrc, const char *fsrc);

    // simple input processing (polled in mainloop)
    void processInput(float deltaTime);

private:
    GLFWwindow *window = nullptr;
    const GLFWvidmode *mode = nullptr;
    GLFWmonitor *monitor = nullptr;

    // GL objects
    unsigned int cubeVAO = 0;
    unsigned int cubeVBO = 0;
    unsigned int shaderProgram = 0;

    // camera
    glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 5.0f);
    glm::vec3 camFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 camUp = glm::vec3(0.0f, 1.0f, 0.0f);

    float yaw = -90.0f;
    float pitch = 0.0f;
    // mouse look
    float lastX = 400.0f;
    float lastY = 300.0f;
    bool firstMouse = true;
    float sensitivity = 0.1f;

    void mouseCallback(double xpos, double ypos);

    // timing
    float lastFrame = 0.0f;
    float deltaTime = 0.0f;
};

#endif // APP_H