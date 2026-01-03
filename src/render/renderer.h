#ifndef RENDERER_H
#define RENDERER_H

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>
#include <memory>

#include "render/mesh.h"
#include "render/shader.h"
#include "render/camera.h"

class Renderer
{
public:

    void draw(const Camera &camera);
    void init();

private:
    std::vector<std::unique_ptr<Mesh>> m_meshes;
    std::unique_ptr<Shader> m_shader;
};

#endif
