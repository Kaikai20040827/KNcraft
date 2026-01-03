#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>

#include "core/debug.h"

enum VideoMode
{
    Fullscreen,
    Borderless,
    Windowed
};

class Window
{
public:
    void init(VideoMode videoMode, std::string title);
    Window();
    ~Window();

    GLFWwindow *m_Window;

private:
    std::string m_Title;
    const GLFWvidmode *m_Mode;
    GLFWmonitor *m_Moniter;

    VideoMode m_VideoMode;
};

#endif
