#include "chunk_manager.h"
#include <cmath>
#include <algorithm>

ChunkManager::ChunkManager()
    : loadRadius(1), chunkSize(16.0f)
{
}

ChunkManager::~ChunkManager()
{
    for (auto &p : entries)
    {
        if (p.second.mesh)
            delete p.second.mesh;
    }
    entries.clear();
}

void ChunkManager::update(const glm::vec3 &playerPosition)
{
    int cx = static_cast<int>(std::floor(playerPosition.x / chunkSize));
    int cz = static_cast<int>(std::floor(playerPosition.z / chunkSize));

    // Required coords: center and 4 neighbors (N,S,E,W)
    std::set<std::pair<int, int>> required;

    for(int i=1; i <= 8; i++) {
        for (int j=1; j <= 8; j++) {
            required.emplace(cx + i - 4, cz + j - 4);
        }
    }

    // Create missing chunks
    for (const auto &coord : required)
    {
        if (entries.find(coord) == entries.end())
        {
            Entry e;
            float centerX = coord.first * chunkSize;
            float centerZ = coord.second * chunkSize;
            glm::vec3 center(centerX, 0.0f, centerZ);

            e.chunk.generate(center);
            std::vector<float> vb = e.chunk.buildVertexBuffer();
            e.mesh = new ChunkMesh();
            e.mesh->build(vb);

            entries.emplace(coord, std::move(e));
        }
    }

    // Remove chunks that are no longer required
    std::vector<std::pair<int, int>> toRemove;
    for (const auto &p : entries)
    {
        if (required.find(p.first) == required.end())
            toRemove.push_back(p.first);
    }

    for (const auto &key : toRemove)
    {
        auto it = entries.find(key);
        if (it != entries.end())
        {
            if (it->second.mesh)
                delete it->second.mesh;
            entries.erase(it);
        }
    }
}

std::vector<ChunkMesh *> ChunkManager::getMeshes() const
{
    std::vector<ChunkMesh *> meshes;
    meshes.reserve(entries.size());
    for (const auto &p : entries)
    {
        meshes.push_back(p.second.mesh);
    }
    return meshes;
}
