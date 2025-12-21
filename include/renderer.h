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
                const std::vector<ChunkMesh *> &meshes, 
                const std::string &top_path,
                const std::string &bottom_path,
                const std::string &front_path,
                const std::string &back_path,
                const std::string &left_path,
                const std::string &right_path);
    void clear();
    void setClearColor(float r, float g, float b, float a);

private:
    Shader *shader;
    ChunkMesh *mesh;
    glm::mat4 model;
    Texture *block;
};

#endif
