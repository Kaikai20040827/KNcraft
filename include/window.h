#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>

#include "debug.h"

typedef enum VideoMode
{
    FULLSCREEN,
    BORDERLESS,
    WINDOW
};

class Window
{
public:
    void init(VideoMode videoMode, const char* title);

    ~Window();
    
    GLFWwindow *window;
private:

    const char* title;
    const GLFWvidmode *mode;
    GLFWmonitor *moniter;

    VideoMode videoMode;
};

#endif
