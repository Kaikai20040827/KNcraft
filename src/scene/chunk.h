#ifndef CHUNK_H
#define CHUNK_H

#define CHUNK_LENGTH 16
#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 16

#define BLOCK_LENGTH 1.0f // length/width/height of one block

#include <glm/glm.hpp>

#include "core/debug.h"

#include <vector>

class Chunk
{
public:
    Chunk();
    ~Chunk();

    std::vector<float> getVertices() const;
    std::vector<unsigned int> getIndices() const;

    void createChunk(float centerX, float CenterY, float centerZ);

private:
    float m_centerX;
    float m_centerY;
    float m_centerZ;

    int m_size;
    std::vector<glm::vec3> m_coords;
};

#endif
