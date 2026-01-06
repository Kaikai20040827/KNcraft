#include "app.h"

App::App(std::string name)
{
    m_Name = name;
}

App::~App()
{
}

void App::run()
{
    LOG("Initializing a new window...");
    m_Window.init(Borderless, m_Name);
    LOG("Initializing done");

    LOG("Initializing GLEW...");
    initGlew();
    LOG("Initializing done");

    LOG("Initializing Renderer...");
    m_Renderer.init();
    LOG("Initializing done");

    LOG("Initializing Camera...");
    m_Camera.init();
    LOG("Initializing Camera done");

    // capture mouse for FPS-like look
    glfwSetInputMode(m_Window.m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSwapInterval(1);

    // darker background for better visibility of green points
    GLCall(glClearColor(1.0f, 0.6f, 1.0f, 1.0f));

    mainLoop();
}

void App::initGlew()
{
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        exit(-1);
    }
    GLCall(const GLubyte *version = glGetString(GL_VERSION));
    std::cout << "<========== OpenGL: " << version << " ==========>" << '\n';

    int width, height;
    GLCall(glfwGetFramebufferSize(m_Window.m_Window, &width, &height));
    GLCall(glViewport(0, 0, width, height));
    // enable depth testing for 3D rendering
    GLCall(glEnable(GL_DEPTH_TEST));
    // update camera aspect ratio to match window
    m_Camera.setAspect((float)width / (float)height);
}

void App::mainLoop()
{

    double lastTime = glfwGetTime();
    double lastX = 640.0, lastY = 360.0;
    bool firstMouse = true;

    while (!glfwWindowShouldClose(m_Window.m_Window))
    {
        double currentTime = glfwGetTime();
        float deltaTime = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime;

        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        // mouse
        double xpos, ypos;
        glfwGetCursorPos(m_Window.m_Window, &xpos, &ypos);
        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }
        float xoffset = static_cast<float>(xpos - lastX);
        float yoffset = static_cast<float>(lastY - ypos); // reversed
        lastX = xpos;
        lastY = ypos;
        m_Camera.processMouseMovement(xoffset, yoffset);

        double last = glfwGetTime();
        // keyboard movement
        double current = 0;
        if (glfwGetKey(m_Window.m_Window, GLFW_KEY_W) == GLFW_PRESS)
        {
            current = glfwGetTime();
            float gap = static_cast<float>(current - last);
            if (gap <= 0.7f)
                m_Camera.processKeyboard(CameraMovement::RunForward, deltaTime);
            else
                m_Camera.processKeyboard(CameraMovement::Forward, deltaTime);
        }
        if (glfwGetKey(m_Window.m_Window, GLFW_KEY_S) == GLFW_PRESS)
            m_Camera.processKeyboard(CameraMovement::Backward, deltaTime);
        if (glfwGetKey(m_Window.m_Window, GLFW_KEY_A) == GLFW_PRESS)
            m_Camera.processKeyboard(CameraMovement::Left, deltaTime);
        if (glfwGetKey(m_Window.m_Window, GLFW_KEY_D) == GLFW_PRESS)
            m_Camera.processKeyboard(CameraMovement::Right, deltaTime);
        if (glfwGetKey(m_Window.m_Window, GLFW_KEY_SPACE) == GLFW_PRESS)
            m_Camera.processKeyboard(CameraMovement::Jump, deltaTime);
        if (glfwGetKey(m_Window.m_Window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            m_Camera.processKeyboard(CameraMovement::Crouch, deltaTime);

        m_Camera.update(deltaTime);

        LOG("Renderer drawing...");
        m_Renderer.draw(m_Camera);
        LOG("Renderer drawing done");

        GLCall(glfwSwapBuffers(m_Window.m_Window));
        GLCall(glfwPollEvents());
    }
}
