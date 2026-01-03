#include "render/ibo.h"

Ibo::Ibo()
{
    LOG("Generating IBO");
    GLCall(glGenBuffers(1, &m_Ibo));
    LOG("Generating IBO done");

    bind();
}

Ibo::~Ibo()
{
}

void Ibo::setData(const Chunk &chunk)
{
    LOG("Setting index data");
    m_Indices = chunk.getIndices();
    int coordCount = (CHUNK_LENGTH + 1) * (CHUNK_WIDTH + 1) * (CHUNK_HEIGHT + 1);
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), m_Indices.data(), GL_STATIC_DRAW));
    LOG("Setting index data done");
}

void Ibo::bind()
{
    LOG("Binding IBO");
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo));
    LOG("Binding IBO done");
}
