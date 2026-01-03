#ifndef MESH_H
#define MESH_H

#define CHUNK_NUMBER 12 * 12

#include "render/ibo.h"
#include "render/vbo.h"
#include "render/vao.h"
#include "core/debug.h"
#include "scene/chunk.h"

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
    Chunk m_chunk;

    Vbo m_vbo;
    Ibo m_ibo;
    Vao m_vao;
};

#endif