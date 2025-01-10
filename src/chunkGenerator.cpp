#include "chunkGenerator.h"

ChunkGenerator::ChunkGenerator() { }
ChunkGenerator::~ChunkGenerator() { }

std::vector<unsigned int> ChunkGenerator::generateChunkData(std::vector<unsigned int>& oldData, int size)
{
    int chunkZ = 16;
    int chunkX = 16;
    float scale = 10.0f; // Zoom On Noise
    std::vector<unsigned int> newData = oldData;

    for (int y = 0; y < size; y++)
    {
        for (int z = 0; z < chunkZ; ++z)
        {
            for (int x = 0; x < chunkX; ++x)
            {
                float noise = PerlinNoise::perlin2D(z, x, scale);
                if (noise < 0.3f)
                {
                    newData.push_back(BlockUtils::BlockType::DIRT);
                }
                else if (noise < 0.6f)
                {
                    newData.push_back(BlockUtils::BlockType::STONE);
                }
                else if (noise < 0.8f)
                {
                    newData.push_back(BlockUtils::BlockType::GRASS);
                }
                else
                {
                    newData.push_back(BlockUtils::BlockType::AIR);
                }
            }
        }
    }
    return newData;
}
