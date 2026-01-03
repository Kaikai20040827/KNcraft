#include "render/mesh.h"

Mesh::Mesh(float centerX,
           float centerY,
           float centerZ)
{
    m_chunk.createChunk(centerX, centerY, centerZ);

    m_ibo.setData(m_chunk);
    m_vbo.setData(m_chunk);
}

Mesh::~Mesh()
{
}

void Mesh::bind()
{
    LOG("Binding VAO");
    m_vao.bind();
    LOG("Binding VAO done");

    LOG("Binding VBO");
    m_vbo.bind();
    LOG("Binding VBO done");

    LOG("Binding IBO");
    m_ibo.bind();
    LOG("Binding IBO done");

    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void *)0));

    m_vao.unbind();
}

void Mesh::draw()
{
    // bind VAO and draw the chunk as points
    m_vao.bind();
    int coordCount = (CHUNK_LENGTH + 1) * (CHUNK_WIDTH + 1) * (CHUNK_HEIGHT + 1);
    GLCall(glDrawElements(GL_POINTS, coordCount, GL_UNSIGNED_INT, nullptr));
    m_vao.unbind();
}
