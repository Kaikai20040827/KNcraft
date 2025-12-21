#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "mesh.h"

const float vertices[108] = {
    // ================= 前面 (Front, +Z) =================
    -0.5f, -0.5f, 0.5f, // 前面 左下
    0.5f, -0.5f, 0.5f,  // 前面 右下
    0.5f, 0.5f, 0.5f,   // 前面 右上

    0.5f, 0.5f, 0.5f,   // 前面 右上
    -0.5f, 0.5f, 0.5f,  // 前面 左上
    -0.5f, -0.5f, 0.5f, // 前面 左下

    // ================= 后面 (Back, -Z) ==================
    -0.5f, -0.5f, -0.5f, // 后面 左下
    -0.5f, 0.5f, -0.5f,  // 后面 左上
    0.5f, 0.5f, -0.5f,   // 后面 右上

    0.5f, 0.5f, -0.5f,   // 后面 右上
    0.5f, -0.5f, -0.5f,  // 后面 右下
    -0.5f, -0.5f, -0.5f, // 后面 左下

    // ================= 左面 (Left, -X) ==================
    -0.5f, 0.5f, 0.5f,   // 左面 前上
    -0.5f, 0.5f, -0.5f,  // 左面 后上
    -0.5f, -0.5f, -0.5f, // 左面 后下

    -0.5f, -0.5f, -0.5f, // 左面 后下
    -0.5f, -0.5f, 0.5f,  // 左面 前下
    -0.5f, 0.5f, 0.5f,   // 左面 前上

    // ================= 右面 (Right, +X) =================
    0.5f, 0.5f, 0.5f,   // 右面 前上
    0.5f, -0.5f, -0.5f, // 右面 后下
    0.5f, 0.5f, -0.5f,  // 右面 后上

    0.5f, -0.5f, -0.5f, // 右面 后下
    0.5f, 0.5f, 0.5f,   // 右面 前上
    0.5f, -0.5f, 0.5f,  // 右面 前下

    // ================= 上面 (Top, +Y) ==================
    -0.5f, 0.5f, -0.5f, // 上面 左后
    -0.5f, 0.5f, 0.5f,  // 上面 左前
    0.5f, 0.5f, 0.5f,   // 上面 右前

    0.5f, 0.5f, 0.5f,   // 上面 右前
    0.5f, 0.5f, -0.5f,  // 上面 右后
    -0.5f, 0.5f, -0.5f, // 上面 左后

    // ================= 下面 (Bottom, -Y) ===============
    -0.5f, -0.5f, -0.5f, // 下面 左后
    0.5f, -0.5f, 0.5f,   // 下面 右前
    -0.5f, -0.5f, 0.5f,  // 下面 左前

    0.5f, -0.5f, 0.5f,   // 下面 右前
    -0.5f, -0.5f, -0.5f, // 下面 左后
    0.5f, -0.5f, -0.5f   // 下面 右后
};

ChunkMesh::ChunkMesh(Texture&& texture)
:texture(std::move(texture))
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
}

ChunkMesh::~ChunkMesh()
{
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void ChunkMesh::build(const std::vector<float>& vertices)
{
    vertexCount = vertices.size() / 3;

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(float),
        vertices.data(),
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE,
        3 * sizeof(float), (void*)0
    );
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void ChunkMesh::draw() const
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
}