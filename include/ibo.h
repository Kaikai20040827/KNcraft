#ifndef IBO_H
#define IBO_H

#include <GL/glew.h>

#include "debug.h"
#include "chunk.h"

#include <vector>

class Ibo
{
public:
    Ibo();
    ~Ibo();

    void setData(const Chunk& chunk);
    void bind();

private:
    unsigned int ibo;
    std::vector<unsigned int> indices;
};

#endif
