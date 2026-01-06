#ifndef MESH_H
#define MESH_H

#define CHUNK_NUMBER 12 * 12

#include "system/render/ibo.h"
#include "system/render/vbo.h"
#include "system/render/vao.h"
#include "core/debug/debug.h"
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
    Chunk m_Chunk;

    Vbo m_Vbo;
    Ibo m_Ibo;
    Vao m_Vao;
};

#endif