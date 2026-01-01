#include "mesh.h"

Mesh::Mesh(float centerX,
           float centerY,
           float centerZ)
{
    chunk.createChunk(centerX, centerY, centerZ);

    ibo.setData(chunk);
    vbo.setData(chunk);
}

Mesh::~Mesh()
{
}

void Mesh::bind()
{
    LOG("Binding VAO");
    vao.bind();
    LOG("Binding VAO done");

    LOG("Binding VBO");
    vbo.bind();
    LOG("Binding VBO done");

    LOG("Binding IBO");
    ibo.bind();
    LOG("Binding IBO done");

    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void *)0));

    vao.unbind();
}

void Mesh::draw()
{
    // bind VAO and draw the chunk as points
    vao.bind();
    int coordCount = (CHUNK_LENGTH + 1) * (CHUNK_WIDTH + 1) * (CHUNK_HEIGHT + 1);
    GLCall(glDrawElements(GL_POINTS, coordCount, GL_UNSIGNED_INT, nullptr));
    vao.unbind();
}
