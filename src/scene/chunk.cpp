#include "scene/chunk.h"

Chunk::Chunk()
{
    LOG("Initializing chunk size");
    m_size = CHUNK_LENGTH * CHUNK_WIDTH * CHUNK_HEIGHT;
    LOG("Initializing done");
}

Chunk::~Chunk()
{
}

std::vector<float> Chunk::getVertices() const
{
    std::vector<float> vertices;
    vertices.reserve(m_coords.size() * 3);

    for (const auto &v : m_coords)
    {
        vertices.push_back(v.x);
        vertices.push_back(v.y);
        vertices.push_back(v.z);
    }
    return vertices;
}

std::vector<unsigned int> Chunk::getIndices() const
{
    std::vector<unsigned int> indices;
    indices.reserve(m_coords.size());

    for (unsigned int i = 0; i < m_coords.size(); i++)
    {
        indices.push_back(i);
    }
    return indices;
}

void Chunk::createChunk(float centerX, float centerY, float centerZ)
{
    LOG("Creating a chunk");
    m_coords.clear();
    m_coords.reserve((CHUNK_LENGTH + 1) *
                     (CHUNK_WIDTH + 1) *
                     (CHUNK_HEIGHT + 1));

    for (int ix = 0; ix <= CHUNK_LENGTH; ix++)
        for (int iy = 0; iy <= CHUNK_WIDTH; iy++)
            for (int iz = 0; iz <= CHUNK_HEIGHT; iz++)
            {
                float x = centerX - 8.5f + ix * BLOCK_LENGTH;
                float y = centerY - 8.5f + iy * BLOCK_LENGTH;
                float z = centerZ - 8.5f + iz * BLOCK_LENGTH;

                m_coords.emplace_back(x, y, z);
            }
    LOG("Creating done");
}
