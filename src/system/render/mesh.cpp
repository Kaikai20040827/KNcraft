#include "system/render/mesh.h"

Mesh::Mesh(float centerX,
           float centerY,
           float centerZ)
{
    m_Chunk.createChunk(centerX, centerY, centerZ);

    m_Ibo.setData(m_Chunk);
    m_Vbo.setData(m_Chunk);
}

Mesh::~Mesh()
{
}

void Mesh::bind()
{
    LOG("Binding VAO");
    m_Vao.bind();
    LOG("Binding VAO done");

    LOG("Binding VBO");
    m_Vbo.bind();
    LOG("Binding VBO done");

    LOG("Binding IBO");
    m_Ibo.bind();
    LOG("Binding IBO done");

    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void *)0));

    m_Vao.unbind();
}

void Mesh::draw()
{
    // bind VAO and draw the chunk as points
    m_Vao.bind();
    int coordCount = (CHUNK_LENGTH + 1) * (CHUNK_WIDTH + 1) * (CHUNK_HEIGHT + 1);
    GLCall(glDrawElements(GL_POINTS, coordCount, GL_UNSIGNED_INT, nullptr));
    m_Vao.unbind();
}
