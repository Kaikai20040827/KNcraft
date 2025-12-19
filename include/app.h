#ifndef APP_H
#define APP_H

#include <glm/glm.hpp>
#include "window.h"
#include "camera.h"
#include "shader.h"
#include "mesh.h"
#include "renderer.h"
#include "input.h"

class Minecraft
{
public:
    Minecraft();
    ~Minecraft();

    void run();

private:
    void initialize();
    void mainLoop();
    void handleInput();
    void update(float deltaTime);
    void render();
    void cleanup();

    static void mouseCallbackStatic(GLFWwindow *window, double xpos, double ypos);
    void mouseCallback(double xpos, double ypos);

private:
    // Core modules
    Window *window;
    Shader *shader;
    Camera *camera;
    CubeMesh *cube;
    Renderer *renderer;
    InputManager *inputManager;

    // Timing
    float deltaTime, lastFrame;
};

#endif