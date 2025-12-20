#ifndef RENDERER_H
#define RENDERER_H

#include <glm/glm.hpp>

#include "shader.h"
#include "mesh.h"
#include <vector>

class Renderer
{
public:
    Renderer(Shader *shader);
    ~Renderer();

    void render(const glm::mat4 &view, const glm::mat4 &projection,
                const std::vector<ChunkMesh *> &meshes);
    void clear();
    void setClearColor(float r, float g, float b, float a);

private:
    Shader *shader;
    ChunkMesh *mesh;
    glm::mat4 model;
};

#endif
