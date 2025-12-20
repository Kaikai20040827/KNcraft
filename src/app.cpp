#include "app.h"
#include <glm/gtc/matrix_transform.hpp>

Minecraft::Minecraft()
    : window(nullptr), shader(nullptr), camera(nullptr),
      chunkManager(nullptr), renderer(nullptr), inputManager(nullptr),
      deltaTime(0.0f), lastFrame(0.0f)
{
}

Minecraft::~Minecraft()
{
    cleanup();
}

void Minecraft::run()
{
    initialize();
    mainLoop();
}

void Minecraft::initialize()
{
    // Initialize window (1280x720, windowed mode)
    window = new Window(1280, 720, "Minecraft");

    // Set up mouse input mode
    window->setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Register mouse callback
    glfwSetWindowUserPointer(window->getHandle(), this);
    glfwSetCursorPosCallback(window->getHandle(), Minecraft::mouseCallbackStatic);

    // Initialize shader with vertex and fragment source
    const char *vertexSrc = R"GLSL(
#version 330 core
layout(location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
)GLSL";

    const char *fragmentSrc = R"GLSL(
#version 330 core
out vec4 FragColor;
uniform vec4 uColor;

void main()
{
    FragColor = uColor;
}
)GLSL";

    shader = new Shader(vertexSrc, fragmentSrc);

    // Initialize camera
    camera = new Camera();

    // Initialize cube mesh
    // Initialize chunk manager (handles creating per-chunk meshes)
    chunkManager = new ChunkManager();

    // Initialize renderer
    renderer = new Renderer(shader);
    renderer->setClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    // Initialize input manager
    inputManager = new InputManager();
}

void Minecraft::mainLoop()
{
    lastFrame = 0.0f;

    while (!window->shouldClose())
    {
        // Update timing
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Process input and update
        handleInput();
        update(deltaTime);

        // Render
        render();

        // Swap buffers and poll events
        window->swapBuffers();
        window->pollEvents();
    }
}

void Minecraft::handleInput()
{
    bool w, s, a, d, space, shift;
    inputManager->processKeyboard(window->getHandle(), deltaTime, w, s, a, d, space, shift);
    camera->processKeyboard(deltaTime, w, s, a, d, space, shift);
}

void Minecraft::update(float deltaTime)
{
    // Update chunks around player
    if (chunkManager && camera)
        chunkManager->update(camera->position);
}

void Minecraft::render()
{
    renderer->clear();

    // Get view and projection matrices
    glm::mat4 view = camera->getViewMatrix();
    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        window->getAspectRatio(),
        0.1f,
        100.0f);

    // Get chunk meshes and render scene
    std::vector<ChunkMesh *> meshes = chunkManager->getMeshes();
    renderer->render(view, projection, meshes);
}

void Minecraft::cleanup()
{
    delete renderer;
    delete inputManager;
    delete chunkManager;
    delete shader;
    delete camera;
    delete window;
}

void Minecraft::mouseCallbackStatic(GLFWwindow *window, double xpos, double ypos)
{
    Minecraft *app = static_cast<Minecraft *>(glfwGetWindowUserPointer(window));
    if (app)
    {
        app->mouseCallback(xpos, ypos);
    }
}

void Minecraft::mouseCallback(double xpos, double ypos)
{
    inputManager->processMouse(xpos, ypos);
    glm::vec2 mouseDelta = inputManager->getMouseDelta();

    // Pass mouse delta to camera for view rotation
    camera->processMouse(mouseDelta.x, mouseDelta.y);
}
