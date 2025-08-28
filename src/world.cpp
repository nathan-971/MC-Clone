#include "world.h"

World::World(glm::vec3 camPos, unsigned int size, unsigned int program) 
{
	this->camPos = camPos;
	this->worldSize = size;
	this->shaderProgram = program;
	generateWorld();
}

World::~World()
{
	for (auto& pair : this->chunks)
	{
		delete pair.second;
	}
	chunks.clear();
}

void World::generateWorld()
{
	std::vector<ChunkCoordinates> allChunkCoordinates;
	for (int x = this->camPos.x; x < this->worldSize; x++)
	{
		for (int z = this->camPos.z; z < this->worldSize; z++)
		{
			ChunkCoordinates coord{ x, z };
			allChunkCoordinates.push_back(coord);
		}
	}

	for (ChunkCoordinates& cc : allChunkCoordinates)
	{
		this->chunks.insert(std::make_pair(cc, new Chunk(CHUNK_XZ_SIZE, CHUNK_Y_SIZE, glm::vec3(cc.x, 0, cc.z))));
	}

	for (const auto& pair : this->chunks)
	{
		ChunkCoordinates cc = pair.first;
		Chunk* c = pair.second;
		c->neighbours[ChunkNeighbours::NORTH] = getChunkAt(cc.x, cc.z + 1);
		c->neighbours[ChunkNeighbours::SOUTH] = getChunkAt(cc.x, cc.z - 1);
		c->neighbours[ChunkNeighbours::EAST] = getChunkAt(cc.x + 1, cc.z);
		c->neighbours[ChunkNeighbours::WEST] = getChunkAt(cc.x - 1, cc.z);
		c->generateChunk();
	}
}

void World::renderWorld()
{
	for (const auto& pair : this->chunks)
	{
		pair.second->renderChunk(this->shaderProgram);
	}
}

Chunk* World::getChunkAt(int x, int z)
{
	ChunkCoordinates cc{ x, z };
	auto keyPair = this->chunks.find(cc);
	if (keyPair != this->chunks.end())
	{
		return keyPair->second;
	}
	return nullptr;
}