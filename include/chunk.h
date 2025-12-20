#ifndef CHUNK_H
#define CHUNK_H

#include <glm/glm.hpp>

#include "mesh.h"

#include <vector>
#include <array>

class Chunk
{
public:
    Chunk()
    {
        chunkSize = 16 * 16;
    }
    ~Chunk()
    {
        blocks.clear();
        chunkSize = 0;
    };

    void generate(glm::vec3 chunkCenter);
    std::vector<float> buildVertexBuffer() const;

public:
    std::vector<std::array<float, 108>> blocks; // Example block storage
    int chunkSize;
};

#endif // CHUNK_H