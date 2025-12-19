#ifndef RENDERER_H
#define RENDERER_H

#include <glm/glm.hpp>

class Shader;
class CubeMesh;

class Renderer
{
public:
    Renderer(Shader *shader, CubeMesh *mesh);
    ~Renderer();

    void render(const glm::mat4 &view, const glm::mat4 &projection);
    void clear();
    void setClearColor(float r, float g, float b, float a);

private:
    Shader *shader;
    CubeMesh *mesh;
    glm::mat4 model;
};

#endif
