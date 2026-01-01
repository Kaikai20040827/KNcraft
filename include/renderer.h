#ifndef RENDERER_H
#define RENDERER_H

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>

#include "mesh.h"
#include "shader.h"
#include "camera.h"

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void draw(const Camera &camera);
    void init();

private:
    std::vector<Mesh*> meshes;
    Shader *shader;
};

#endif
