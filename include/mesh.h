#ifndef MESH_H
#define MESH_H

#define CHUNK_NUMBER 12 * 12

#include "ibo.h"
#include "vbo.h"
#include "vao.h"
#include "debug.h"
#include "chunk.h"

class Mesh
{
public:
    Mesh(float centerX,
         float centerY,
         float centerZ);
    ~Mesh();

    void bind();
    void draw();

private:
    Chunk chunk;

    Vbo vbo;
    Ibo ibo;
    Vao vao;
};

#endif