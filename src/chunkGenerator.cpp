#include "chunkGenerator.h"

std::vector<unsigned int> ChunkGenerator::generateChunkData(int chunkWidth, int chunkHeight)
{
    float scale = 50.0f; // Zoom On Noise
    std::vector<unsigned int> newData;
    newData.reserve(chunkWidth * chunkWidth * chunkHeight);
    //std::cout << "Chunk Height:" << chunkHeight << "\n";
    for (int y = 0; y < chunkHeight; y++)
    {
        //std::cout << "Y:" << y << "\n";
        for (int z = 0; z < chunkWidth; z++)
        {
            for (int x = 0; x < chunkWidth; x++)
            {    
                if (y <= 16)
                {
                    newData.push_back(BlockUtils::BlockType::DIRT);
                }
                else if (y >= 17 && y <= 30)
                {
                    newData.push_back(BlockUtils::BlockType::DIRT);
                }
                else
                {
                    float noise = PerlinNoise::perlin2D(z, x, scale);
                    if (noise < 0.5)
                    {
                        newData.push_back(BlockUtils::BlockType::DIRT);
                    }
                    else
                    {
                        newData.push_back(BlockUtils::BlockType::AIR);
                    }
                }
            }
        }
    }
    return newData;
}