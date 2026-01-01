#include "renderer.h"

Renderer::Renderer()
    : shader(nullptr)
{
    meshes.reserve((12 * 2 + 1) * (12 * 2 + 1));
    for (auto mesh : meshes)
    {
        mesh = nullptr;
    }
}

Renderer::~Renderer()
{
    if (shader)
        delete shader;

    for (auto mesh : meshes)
    {
        if (mesh)
            delete mesh;
    }
}

void Renderer::init()
{
    LOG("Creating single renderable mesh (one chunk)");
    // create one chunk centered at origin
    for (auto m : meshes)
    {
        if (m)
            delete m;
    }
    meshes.clear();
    meshes.push_back(new Mesh(0.0f, 0.0f, 0.0f));
    LOG("Created 1 mesh");

    LOG("Creating a new shader...");
    shader = new Shader("../../assets/shaders/basic.glsl");
    LOG("Creating a new shader done");

    LOG("Binding a shader...");
    shader->bind();
    LOG("Binding a shader done");

    LOG("Setting matrices...");
    shader->setUniformMat4f("model", glm::mat4(1.f));
    shader->setUniformMat4f("view", glm::mat4(1.f));
    shader->setUniformMat4f("projection", glm::mat4(1.f));
    LOG("Setting matrices done");

    LOG("Setting color...");
    shader->setUniform4f("u_Color", 0.0f, 1.0f, 0.0f, 1.0f); // green color
    LOG("Setting color done");

    // allow vertex shader to set point size (so GL_POINTS are visible)
    GLCall(glEnable(GL_PROGRAM_POINT_SIZE));

    LOG("Binding a mesh...");
    // prepare VAO/VBO/IBO for the single mesh
    if (!meshes.empty() && meshes[0])
        meshes[0]->bind();
    LOG("Binding a mesh done");
}

void Renderer::draw(const Camera &camera)
{
    if (!shader)
    {
        ERR("No shader in renderer");
        return;
    }

    // ensure points are large enough for debugging
    GLCall(glPointSize(20.0f));
    // temporarily disable depth test for point debugging
    GLCall(glDisable(GL_DEPTH_TEST));

    shader->bind();
    // ensure color is set each frame (make points clearly green)
    shader->setUniform4f("u_Color", 0.0f, 1.0f, 0.0f, 1.0f);
    shader->setUniformMat4f("model", glm::mat4(1.f));
    shader->setUniformMat4f("view", camera.getView());
    shader->setUniformMat4f("projection", camera.getProjection());

    // --- DEBUG: draw a simple triangle to verify pipeline ---
    {
        float triVerts[] = {
            0.0f,
            0.5f,
            -1.0f,
            -0.5f,
            -0.5f,
            -1.0f,
            0.5f,
            -0.5f,
            -1.0f,
        };
        unsigned int dbgVao, dbgVbo;
        GLCall(glGenVertexArrays(1, &dbgVao));
        GLCall(glBindVertexArray(dbgVao));
        GLCall(glGenBuffers(1, &dbgVbo));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, dbgVbo));
        GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(triVerts), triVerts, GL_STATIC_DRAW));
        GLCall(glEnableVertexAttribArray(0));
        GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void *)0));
        // draw triangle in yellow
        shader->setUniform4f("u_Color", 1.0f, 1.0f, 0.0f, 1.0f);
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));
        // cleanup
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        GLCall(glBindVertexArray(0));
        GLCall(glDeleteBuffers(1, &dbgVbo));
        GLCall(glDeleteVertexArrays(1, &dbgVao));
        // restore green color
        shader->setUniform4f("u_Color", 0.0f, 1.0f, 0.0f, 1.0f);
    }
    // --- end debug triangle ---

    // draw only the first mesh (single chunk)
    if (!meshes.empty() && meshes[0])
    {
        meshes[0]->draw();
    }

    // restore depth testing
    GLCall(glEnable(GL_DEPTH_TEST));
}