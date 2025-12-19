#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Window
{
public:
    Window(int width, int height, const std::string &title);
    ~Window();

    bool shouldClose() const;
    void pollEvents();
    void swapBuffers();
    void setInputMode(int mode, int value);

    GLFWwindow *getHandle() const;
    int getWidth() const;
    int getHeight() const;
    float getAspectRatio() const;

private:
    GLFWwindow *window;
    GLFWmonitor *monitor;
    const GLFWvidmode *mode;
    int width, height;

    void initGLFW();
    void initGLEW();
    void setupContext();
};

#endif
