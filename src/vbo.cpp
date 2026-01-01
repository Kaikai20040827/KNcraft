#include "vbo.h"

Vbo::Vbo()
{
    LOG("Generating VBO");
    GLCall(glGenBuffers(1, &vbo));
    LOG("Generating VBO done");

    bind();
}

Vbo::~Vbo()
{
}

void Vbo::setData(const Chunk &chunk)
{
    LOG("Setting vertex data");
    vertices = chunk.getVertices();
    int coordCount = (CHUNK_LENGTH + 1) * (CHUNK_WIDTH + 1) * (CHUNK_HEIGHT + 1);
    GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW));
    LOG("Setting vertex data done");
}

void Vbo::bind()
{
    LOG("Binding VBO");
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    LOG("Binding VBO done");
}
