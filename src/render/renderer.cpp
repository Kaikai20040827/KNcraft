#include "render/renderer.h"

void Renderer::init()
{
    LOG("Clearing mesh container...");
    m_meshes.clear();
    LOG("Clearing mesh container done");

    LOG("Creating single renderable mesh (one chunk)");
    // create one chunk centered at origin
    m_meshes.emplace_back(std::make_unique<Mesh>(0.f, 0.f, 0.f));
    LOG("Created 1 mesh");

    LOG("Creating a new shader...");
    m_shader = std::make_unique<Shader>("../../../assets/shaders/basic.glsl");
    LOG("Creating a new shader done");

    LOG("Binding a shader...");
    m_shader->bind();
    LOG("Binding a shader done");

    LOG("Setting matrices...");
    m_shader->setUniformMat4f("model", glm::mat4(1.f));
    m_shader->setUniformMat4f("view", glm::mat4(1.f));
    m_shader->setUniformMat4f("projection", glm::mat4(1.f));
    LOG("Setting matrices done");

    LOG("Setting color...");
    m_shader->setUniform4f("u_Color", 0.0f, 1.0f, 0.0f, 1.0f); // green color
    LOG("Setting color done");

    // allow vertex m_shader to set point size (so GL_POINTS are visible)
    GLCall(glEnable(GL_PROGRAM_POINT_SIZE));

    LOG("Binding a mesh...");
    // prepare VAO/VBO/IBO for the single mesh
    if (!m_meshes.empty() && m_meshes[0])
        m_meshes[0]->bind();
    LOG("Binding a mesh done");
}

void Renderer::draw(const Camera &camera)
{
    if (!m_shader)
    {
        ERR("No shader in renderer");
        return;
    }

    // ensure points are large enough for debugging
    GLCall(glPointSize(20.0f));
    // temporarily disable depth test for point debugging
    GLCall(glDisable(GL_DEPTH_TEST));

    m_shader->bind();
    // ensure color is set each frame (make points clearly green)
    m_shader->setUniform4f("u_Color", 0.0f, 1.0f, 0.0f, 1.0f);
    m_shader->setUniformMat4f("model", glm::mat4(1.f));
    m_shader->setUniformMat4f("view", camera.getView());
    m_shader->setUniformMat4f("projection", camera.getProjection());

    // draw only the first mesh (single chunk)
    if (!m_meshes.empty() && m_meshes[0])
    {
        m_meshes[0]->draw();
    }

    // restore depth testing
    GLCall(glEnable(GL_DEPTH_TEST));
}