#ifndef RENDERER_H
#define RENDERER_H

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>
#include <memory>

#include "system/render/mesh.h"
#include "system/render/shader.h"
#include "system/render/camera.h"

class Renderer
{
public:

    void draw(const Camera &camera);
    void init();

private:
    std::vector<std::unique_ptr<Mesh>> m_Meshes;
    std::unique_ptr<Shader> m_Shader;
};

#endif
