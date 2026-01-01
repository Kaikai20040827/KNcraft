#include "window.h"

Window::~Window()
{
    // GLCall(glfwTerminate());
}

void Window::init(VideoMode videoMode, const char *title)
{
    LOG("Initializing GLFW...");
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize a window" << std::endl;
        exit(-1);
    }
    this->title = title;
    LOG("Initializing GLFW done");

    LOG("Setting VideoMode...");

    switch (videoMode)
    {
    case FULLSCREEN:
        LOG("Video mode: FULLSCREEN");
        videoMode = FULLSCREEN;

        moniter = glfwGetPrimaryMonitor();
        mode = glfwGetVideoMode(moniter);

        LOG("Creating a new fullscreen window...");
        window = glfwCreateWindow(mode->width, mode->height, this->title, moniter, nullptr);
        ASSERT(window);
        LOG("Creating a new fullscreen window done");

        break;
    case BORDERLESS:
        LOG("Video mode: BORDERLESS");
        videoMode = BORDERLESS;

        moniter = glfwGetPrimaryMonitor();
        mode = glfwGetVideoMode(moniter);

        LOG("Creating a new borderless window...");
        window = glfwCreateWindow(
                   mode->width,
                   mode->height,
                   this->title,
                   nullptr,
                   nullptr);
        ASSERT(window);
        LOG("Creating a new borderless window done");

        glfwSetWindowPos(window, 0, 0);

            break;
    case WINDOW:
        LOG("Video mode: WINDOW");
        videoMode = WINDOW;

        moniter = glfwGetPrimaryMonitor();
        mode = glfwGetVideoMode(moniter);

        LOG("Creating a new window...");
        window = glfwCreateWindow(
                   1280,
                   720,
                   this->title,
                   nullptr,
                   nullptr);
        LOG("Setting window position in center...");
        glfwSetWindowPos(window, 320, 180);
        LOG("Setting window position in center done");
        ASSERT(window);
        LOG("Creating a new window done");

        break;
    default:
        LOG("Video mode: FULLSCREEN");
        videoMode = FULLSCREEN;

        moniter = glfwGetPrimaryMonitor();
        mode = glfwGetVideoMode(moniter);

        LOG("Creating a new fullscreen window");
        window = glfwCreateWindow(mode->width, mode->height, this->title, moniter, nullptr);
        ASSERT(window);
        LOG("Creating a new fullscreen window done");

        break;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwShowWindow(window);
}
