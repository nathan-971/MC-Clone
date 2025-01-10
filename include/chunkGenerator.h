#ifndef _CHUNK_GENERATOR_H_
#define _CHUNK_GENERATOR_H_

#include "block.h"
#include "perlinNoise.h"
#include <vector>

class ChunkGenerator
{
public:
	std::vector<unsigned int> data;

	ChunkGenerator();
	~ChunkGenerator();
	static std::vector<unsigned int> generateChunkData(std::vector<unsigned int>& oldData, int size);
};

#endif