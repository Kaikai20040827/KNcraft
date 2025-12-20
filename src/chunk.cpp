#include "chunk.h"
#include "mesh.h"

void Chunk::generate(glm::vec3 chunkCenter)
{
    blocks.clear();

    const int counter_width = 16;
    const int counter_height = 16;

    glm::vec3 blockCenter;
    blockCenter.y = chunkCenter.y;
    blockCenter.z = chunkCenter.z - 7.5f;

    for (int i = 0; i < counter_width; i++)
    {
        blockCenter.x = chunkCenter.x - 7.5f;

        for (int j = 0; j < counter_height; j++)
        {
            blockCenter.x += 1.0f;

            int k = 0;
            std::array<float, 108> block_vertices;
            while (k < 108)
            {
                block_vertices[k] = vertices[k] + blockCenter.x;
                block_vertices[k + 1] = vertices[k + 1] + blockCenter.y;
                block_vertices[k + 2] = vertices[k + 2] + blockCenter.z;
                k += 3;
            }
            blocks.push_back(block_vertices);
        }
        blockCenter.z += 1.0f;
    }
}

std::vector<float> Chunk::buildVertexBuffer() const
{
    std::vector<float> buffer;
    buffer.reserve(blocks.size() * 108);

    for (const auto &block : blocks)
    {
        buffer.insert(buffer.end(), block.begin(), block.end());
    }
    return buffer;
}