#include "renderer.h"
#include "shader.h"
#include "mesh.h"
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

Renderer::Renderer(Shader *shader)
    : shader(shader), model(glm::mat4(1.0f)), block(nullptr)
{
}

// Shader and mesh are owned elsewhere

// ensure we clean up allocated texture
// (destructor should be safe if block==nullptr)
Renderer::~Renderer()
{
    if (block)
        delete block;
}

void Renderer::render(const glm::mat4 &view, const glm::mat4 &projection,
                      const std::vector<ChunkMesh *> &meshes,
                      const std::string &top_path,
                      const std::string &bottom_path,
                      const std::string &front_path,
                      const std::string &back_path,
                      const std::string &left_path,
                      const std::string &right_path)
{
    if (block)
        delete block;
    block = new Texture(top_path, bottom_path, front_path, back_path, left_path, right_path);

    shader->use();
    shader->setMat4("model", model);
    shader->setMat4("view", view);
    shader->setMat4("projection", projection);
    // ensure sampler uses texture unit 0
    shader->setInt("uTexture", 0);

    // First pass: filled cubes with base color
    shader->setVec4("uColor", glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    for (const auto &m : meshes)
    {
        if (m)
        {
            block->bind(0);
            m->draw();
        }
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
        {
            block->bind(0);
            m->draw();
        }
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
