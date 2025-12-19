#include "renderer.h"
#include "shader.h"
#include "mesh.h"
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

Renderer::Renderer(Shader *shader, CubeMesh *mesh)
    : shader(shader), mesh(mesh), model(glm::mat4(1.0f))
{
}

Renderer::~Renderer()
{
    // Shader and mesh are owned elsewhere
}

void Renderer::render(const glm::mat4 &view, const glm::mat4 &projection)
{
    shader->use();
    shader->setMat4("model", model);
    shader->setMat4("view", view);
    shader->setMat4("projection", projection);
    mesh->draw();
}

void Renderer::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::setClearColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}
