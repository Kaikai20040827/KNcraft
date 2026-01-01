#include "ibo.h"

Ibo::Ibo()
{
    LOG("Generating IBO");
    GLCall(glGenBuffers(1, &ibo));
    LOG("Generating IBO done");

    bind();
}

Ibo::~Ibo()
{
}

void Ibo::setData(const Chunk &chunk)
{
    LOG("Setting index data");
    indices = chunk.getIndices();
    int coordCount = (CHUNK_LENGTH + 1) * (CHUNK_WIDTH + 1) * (CHUNK_HEIGHT + 1);
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW));
    LOG("Setting index data done");
}

void Ibo::bind()
{
    LOG("Binding IBO");
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    LOG("Binding IBO done");
}
