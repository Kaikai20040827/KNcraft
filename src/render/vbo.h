#ifndef VBO_H
#define VBO_H

#include <GL/glew.h>

#include "scene/chunk.h"
#include "core/debug.h"

#include <vector>

class Vbo
{
public:
    Vbo();
    ~Vbo();

    void setData(const Chunk &chunk);
    void bind();

private:
    unsigned int m_vbo;
    std::vector<float> m_vertices;
};

#endif
