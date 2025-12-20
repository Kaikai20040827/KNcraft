#ifndef CHUNK_MANAGER_H
#define CHUNK_MANAGER_H

#include <map>
#include <vector>
#include <set>
#include <utility>
#include <glm/glm.hpp>

#include "chunk.h"
#include "mesh.h"

class ChunkManager
{
public:
    ChunkManager();
    ~ChunkManager();

    // Update loaded chunks based on player position
    void update(const glm::vec3 &playerPosition);

    // Return list of active ChunkMesh pointers for rendering
    std::vector<ChunkMesh *> getMeshes() const;

private:
    struct Entry
    {
        Chunk chunk;
        ChunkMesh *mesh = nullptr;
    };

    std::map<std::pair<int, int>, Entry> entries;

    int loadRadius;  // in chunks (we'll use 1 for center + 4 neighbors)
    float chunkSize; // world units per chunk (16)
};

#endif // CHUNK_MANAGER_H
