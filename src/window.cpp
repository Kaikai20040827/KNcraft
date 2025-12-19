#include "window.h"
#include <stdexcept>

Window::Window(int width, int height, const std::string &title)
    : window(nullptr), monitor(nullptr), mode(nullptr),
      width(width), height(height)
{
    initGLFW();

    monitor = glfwGetPrimaryMonitor();
    mode = glfwGetVideoMode(monitor);

    int w = (width > 0) ? width : (mode ? mode->width : 1280);
    int h = (height > 0) ? height : (mode ? mode->height : 720);

    window = glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    this->width = w;
    this->height = h;

    initGLEW();
    setupContext();
}

Window::~Window()
{
    if (window)
    {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

void Window::initGLFW()
{
    if (glfwInit() == GLFW_FALSE)
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }
}

void Window::initGLEW()
{
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error("Failed to initialize GLEW");
    }
}

void Window::setupContext()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(window);
}

void Window::pollEvents()
{
    glfwPollEvents();
}

void Window::swapBuffers()
{
    glfwSwapBuffers(window);
}

void Window::setInputMode(int mode, int value)
{
    glfwSetInputMode(window, mode, value);
}

GLFWwindow *Window::getHandle() const
{
    return window;
}

int Window::getWidth() const
{
    return width;
}

int Window::getHeight() const
{
    return height;
}

float Window::getAspectRatio() const
{
    return (height > 0) ? static_cast<float>(width) / static_cast<float>(height) : 4.0f / 3.0f;
}
