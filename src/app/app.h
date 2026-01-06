#ifndef APP_H
#define APP_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>

#include "platform/window.h"
#include "render/renderer.h"
#include "core/debug/debug.h"
#include "render/camera.h"

class App
{
public:
    App::App(std::string name);
    App::~App();
    void run();

private:
    void initGlew();
    void mainLoop();

private:
    std::string m_Name;

    Window m_Window;
    Renderer m_Renderer;
    Camera m_Camera;
};

#endif
