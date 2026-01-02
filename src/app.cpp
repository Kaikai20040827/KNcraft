#include "app.h"

App::App(const char *name)
{
    this->name = name;
}

App::~App()
{
}

void App::run()
{
    LOG("Initializing a new window...");
    window.init(BORDERLESS, name);
    LOG("Initializing done");

    LOG("Initializing GLEW...");
    initGlew();
    LOG("Initializing done");

    LOG("Initializing Renderer...");
    renderer.init();
    LOG("Initializing done");

    LOG("Initializing Camera...");
    camera.init();
    LOG("Initializing Camera done");

    // capture mouse for FPS-like look
    glfwSetInputMode(window.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSwapInterval(1);

    // darker background for better visibility of green points
    GLCall(glClearColor(1.0f, 0.6f, 1.0f, 1.0f));

    mainloop();
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
    GLCall(glfwGetFramebufferSize(window.window, &width, &height));
    GLCall(glViewport(0, 0, width, height));
    // enable depth testing for 3D rendering
    GLCall(glEnable(GL_DEPTH_TEST));
    // update camera aspect ratio to match window
    camera.setAspect((float)width / (float)height);
}

void App::mainloop()
{

    double lastTime = glfwGetTime();
    double lastX = 640.0, lastY = 360.0;
    bool firstMouse = true;

    while (!glfwWindowShouldClose(window.window))
    {
        double currentTime = glfwGetTime();
        float deltaTime = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime;

        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        // mouse
        double xpos, ypos;
        glfwGetCursorPos(window.window, &xpos, &ypos);
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
        camera.processMouseMovement(xoffset, yoffset);

        double last = glfwGetTime();
        // keyboard movement
        double current = 0;
        if (glfwGetKey(window.window, GLFW_KEY_W) == GLFW_PRESS)
        {
            current = glfwGetTime();
            float gap = static_cast<float>(current - last);
            if (gap <= 0.7f)
                camera.processKeyboard(RUN_FORWARD, deltaTime);
            else
                camera.processKeyboard(FORWARD, deltaTime);
        }
        if (glfwGetKey(window.window, GLFW_KEY_S) == GLFW_PRESS)
            camera.processKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window.window, GLFW_KEY_A) == GLFW_PRESS)
            camera.processKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window.window, GLFW_KEY_D) == GLFW_PRESS)
            camera.processKeyboard(RIGHT, deltaTime);
        if (glfwGetKey(window.window, GLFW_KEY_SPACE) == GLFW_PRESS)
            camera.processKeyboard(JUMP, deltaTime);
        if (glfwGetKey(window.window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            camera.processKeyboard(CROUCH, deltaTime);

        camera.update(deltaTime);

        LOG("Renderer drawing...");
        renderer.draw(camera);
        LOG("Renderer drawing done");

        GLCall(glfwSwapBuffers(window.window));
        GLCall(glfwPollEvents());
    }
}
