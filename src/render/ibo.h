#ifndef IBO_H
#define IBO_H

#include <GL/glew.h>

#include "core/debug.h"
#include "scene/chunk.h"

#include <vector>

class Ibo
{
public:
    Ibo();
    ~Ibo();

    void setData(const Chunk &chunk);
    void bind();

private:
    unsigned int m_Ibo;
    std::vector<unsigned int> m_Indices;
};

#endif
