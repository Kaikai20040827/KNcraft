#include "system/render/renderer.h"

void Renderer::init()
{
    LOG("Clearing mesh container...");
    m_Meshes.clear();
    LOG("Clearing mesh container done");

    LOG("Creating single renderable mesh (one chunk)");
    // create one chunk centered at origin
    m_Meshes.emplace_back(std::make_unique<Mesh>(0.f, 0.f, 0.f));
    LOG("Created 1 mesh");

    LOG("Creating a new shader...");
    m_Shader = std::make_unique<Shader>("../../../assets/shaders/basic.glsl");
    LOG("Creating a new shader done");

    LOG("Binding a shader...");
    m_Shader->bind();
    LOG("Binding a shader done");

    LOG("Setting matrices...");
    m_Shader->setUniformMat4f("model", glm::mat4(1.f));
    m_Shader->setUniformMat4f("view", glm::mat4(1.f));
    m_Shader->setUniformMat4f("projection", glm::mat4(1.f));
    LOG("Setting matrices done");

    LOG("Setting color...");
    m_Shader->setUniform4f("u_Color", 0.0f, 1.0f, 0.0f, 1.0f); // green color
    LOG("Setting color done");

    // allow vertex m_Shader to set point size (so GL_POINTS are visible)
    GLCall(glEnable(GL_PROGRAM_POINT_SIZE));

    LOG("Binding a mesh...");
    // prepare VAO/VBO/IBO for the single mesh
    if (!m_Meshes.empty() && m_Meshes[0])
        m_Meshes[0]->bind();
    LOG("Binding a mesh done");
}

void Renderer::draw(const Camera &camera)
{
    if (!m_Shader)
    {
        ERR("No shader in renderer");
        return;
    }

    // ensure points are large enough for debugging
    GLCall(glPointSize(20.0f));
    // temporarily disable depth test for point debugging
    GLCall(glDisable(GL_DEPTH_TEST));

    m_Shader->bind();
    // ensure color is set each frame (make points clearly green)
    m_Shader->setUniform4f("u_Color", 0.0f, 1.0f, 0.0f, 1.0f);
    m_Shader->setUniformMat4f("model", glm::mat4(1.f));
    m_Shader->setUniformMat4f("view", camera.getView());
    m_Shader->setUniformMat4f("projection", camera.getProjection());

    // draw only the first mesh (single chunk)
    if (!m_Meshes.empty() && m_Meshes[0])
    {
        m_Meshes[0]->draw();
    }

    // restore depth testing
    GLCall(glEnable(GL_DEPTH_TEST));
}