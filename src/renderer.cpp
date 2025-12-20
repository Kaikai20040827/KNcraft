#include "renderer.h"
#include "shader.h"
#include "mesh.h"
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

Renderer::Renderer(Shader *shader)
    : shader(shader), model(glm::mat4(1.0f))
{
}

Renderer::~Renderer()
{
    // Shader and mesh are owned elsewhere
}

void Renderer::render(const glm::mat4 &view, const glm::mat4 &projection,
                      const std::vector<ChunkMesh *> &meshes)
{
    shader->use();
    shader->setMat4("model", model);
    shader->setMat4("view", view);
    shader->setMat4("projection", projection);

    // First pass: filled cubes with base color
    shader->setVec4("uColor", glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    for (const auto &m : meshes)
    {
        if (m)
            m->draw();
    }

    // Second pass: thin black outlines
    shader->setVec4("uColor", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    glEnable(GL_POLYGON_OFFSET_LINE);
    glPolygonOffset(-1.0f, -1.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(1.0f);
    for (const auto &m : meshes)
    {
        if (m)
            m->draw();
    }
    // restore
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_POLYGON_OFFSET_LINE);
}

void Renderer::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::setClearColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}
