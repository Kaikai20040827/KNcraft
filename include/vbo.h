#ifndef VBO_H
#define VBO_H

#include <GL/glew.h>

#include "chunk.h"
#include "debug.h"

#include <vector>

class Vbo
{
public:
    Vbo();
    ~Vbo();

    void setData(const Chunk& chunk);
    void bind();

private:
    unsigned int vbo;
    std::vector<float> vertices;
};

#endif
