#ifndef APP_H
#define APP_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>

#include "window.h"
#include "renderer.h"
#include "debug.h"
#include "camera.h"

class App
{
public:
    App::App(const char *name);
    App::~App();
    void run();

private:
    void initGlew();
    void mainloop();

private:
    const char *name;

    Window window;
    Renderer renderer;
    Camera camera;
};

#endif
