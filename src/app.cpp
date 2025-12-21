#include "app.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <fstream>

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
    std::ofstream log("app_init.log", std::ios::app);
    if (log)
        log << "initialize() start" << std::endl;
    // Initialize window (1280x720, windowed mode)
    window = new Window(1920, 1080, "Minecraft");
    if (log)
        log << "window created" << std::endl;

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

out vec3 vWorldPos;

void main()
{
    vec4 worldPos = model * vec4(aPos, 1.0);
    vWorldPos = worldPos.xyz;
    gl_Position = projection * view * worldPos;
}
)GLSL";

    const char *fragmentSrc = R"GLSL(
#version 330 core
in vec3 vWorldPos;
out vec4 FragColor;

uniform sampler2D uTexture;
uniform vec4 uColor;

void main()
{
    // Use XZ coordinates to map texture across blocks
    vec2 uv = fract(vWorldPos.xz);
    vec4 tex = texture(uTexture, uv);
    FragColor = tex * uColor;
}
)GLSL";

    shader = new Shader(vertexSrc, fragmentSrc);
    if (log)
        log << "shader created" << std::endl;

    // Initialize camera
    camera = new Camera();

    // Initialize cube mesh
    // Initialize chunk manager (handles creating per-chunk meshes)
    chunkManager = new ChunkManager();

    // Initialize renderer
    renderer = new Renderer(shader);
    renderer->setClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    if (log)
        log << "renderer created" << std::endl;

    // Initialize input manager
    inputManager = new InputManager();

    if (log)
        log << "input manager created" << std::endl;

    block = new Texture("../../textures/grass/grass-side.png",
                        "../../textures/grass/grass-side.png",
                        "../../textures/grass/grass-up.png",
                        "../../textures/grass/grass-down.png",
                        "../../textures/grass/grass-side.png",
                        "../../textures/grass/grass-side.png");
    if (log)
        log << "initial block texture created" << std::endl;
    if (log)
        log.close();
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
    std::vector<ChunkMesh *> meshes = chunkManager->getMeshes(); //  加载区块
    renderer->render(view, projection, meshes,
                    "../../textures/grass/grass-side.png",
                    "../../textures/grass/grass-side.png",
                    "../../textures/grass/grass-up.png",
                    "../../textures/grass/grass-down.png",
                    "../../textures/grass/grass-side.png",
                    "../../textures/grass/grass-side.png"); //  渲染
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
