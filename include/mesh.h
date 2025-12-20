#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <vector>

extern const float vertices[108];

class ChunkMesh
{
public:
    ChunkMesh();
    ~ChunkMesh();

    void build(const std::vector<float>& vertices);
    void draw() const;

private:
    unsigned int VAO = 0;
    unsigned int VBO = 0;
    unsigned int vertexCount = 0;
};

#endif
