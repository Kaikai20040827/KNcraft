#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <vector>

#include "texture.h"

extern const float vertices[108];


class ChunkMesh
{
public:
    ChunkMesh(Texture&& texture);
    ~ChunkMesh();

    void build(const std::vector<float>& vertices);
    void draw() const;
 
private:
    unsigned int VAO = 0;
    unsigned int VBO = 0;
    unsigned int vertexCount = 0;
    
    Texture texture;
};

#endif
