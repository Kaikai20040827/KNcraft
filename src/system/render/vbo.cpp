#include "system/render/vbo.h"

Vbo::Vbo()
{
    LOG("Generating VBO");
    GLCall(glGenBuffers(1, &m_Vbo));
    LOG("Generating VBO done");

    bind();
}

Vbo::~Vbo()
{
}

void Vbo::setData(const Chunk &chunk)
{
    LOG("Setting vertex data");
    m_Vertices = chunk.getVertices();
    int coordCount = (CHUNK_LENGTH + 1) * (CHUNK_WIDTH + 1) * (CHUNK_HEIGHT + 1);
    GLCall(glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(float), m_Vertices.data(), GL_STATIC_DRAW));
    LOG("Setting vertex data done");
}

void Vbo::bind()
{
    LOG("Binding VBO");
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Vbo));
    LOG("Binding VBO done");
}
