#include "platform/window.h"

Window::Window()
{
    m_Window = nullptr;
}

Window::~Window()
{
    if (m_Window)
        glfwDestroyWindow(m_Window);
}

void Window::init(VideoMode videoMode, std::string title)
{
    LOG("Initializing GLFW...");
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize a window" << std::endl;
        exit(-1);
    }
    m_Title = title;
    LOG("Initializing GLFW done");

    LOG("Setting VideoMode...");

    switch (videoMode)
    {
    case Fullscreen:
        LOG("Video Mode: FULLSCREEN");
        videoMode = Fullscreen;

        m_Moniter = glfwGetPrimaryMonitor();
        m_Mode = glfwGetVideoMode(m_Moniter);

        LOG("Creating a new fullscreen window...");
        m_Window = glfwCreateWindow(
            m_Mode->width,
            m_Mode->height,
            m_Title.c_str(),
            m_Moniter,
            nullptr);
        ASSERT(m_Window);
        LOG("Creating a new fullscreen window done");

        break;
    case Borderless:
        LOG("Video mode: BORDERLESS");
        videoMode = Borderless;

        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        m_Moniter = glfwGetPrimaryMonitor();
        m_Mode = glfwGetVideoMode(m_Moniter);

        LOG("Creating a new borderless window...");
        m_Window = glfwCreateWindow(
            m_Mode->width,
            m_Mode->height,
            m_Title.c_str(),
            nullptr,
            nullptr);
        ASSERT(m_Window);
        LOG("Creating a new borderless window done");

        glfwSetWindowPos(m_Window, 0, 0);

        break;
    case Windowed:
        LOG("Video Mode: WINDOW");
        videoMode = Windowed;

        m_Moniter = glfwGetPrimaryMonitor();
        m_Mode = glfwGetVideoMode(m_Moniter);

        LOG("Creating a new window...");
        m_Window = glfwCreateWindow(
            1280,
            720,
            m_Title.c_str(),
            nullptr,
            nullptr);
        LOG("Setting window position in center...");
        glfwSetWindowPos(m_Window, 320, 180);
        LOG("Setting window position in center done");
        ASSERT(m_Window);
        LOG("Creating a new window done");

        break;

    default:
        LOG("Video Mode: FULLSCREEN");
        videoMode = Fullscreen;

        m_Moniter = glfwGetPrimaryMonitor();
        m_Mode = glfwGetVideoMode(m_Moniter);

        LOG("Creating a new fullscreen window");
        m_Window = glfwCreateWindow(
            m_Mode->width,
            m_Mode->height,
            m_Title.c_str(),
            m_Moniter,
            nullptr);
        ASSERT(m_Window);
        LOG("Creating a new fullscreen window done");

        break;
    }
    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(1);
    glfwShowWindow(m_Window);
}
