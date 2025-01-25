#ifndef _CHUNK_GENERATOR_H_
#define _CHUNK_GENERATOR_H_

#include "block.h"
#include "perlinNoise.h"
#include <vector>

class ChunkGenerator
{
public:
	static std::vector<unsigned int> generateChunkData(int chunkWidth, int chunkHeight);
};

#endif