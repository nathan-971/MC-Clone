#ifndef _WORLD_H_
#define _WORLD_H_

#define CHUNK_XZ_SIZE 16
#define CHUNK_Y_SIZE 256

#include <vector>
#include <unordered_map>

#include "chunk.h"

struct ChunkCoordinates 
{
	int x;
	int z;

	bool operator==(const ChunkCoordinates& other) const
	{
		return this->x == other.x && this->z == other.z;
	}
};

struct ChunkCoordinatesHash
{
	std::size_t operator()(const ChunkCoordinates& cc) const noexcept
	{
		std::size_t hash1 = std::hash<int>{}(cc.x);
		std::size_t hash2 = std::hash<int>{}(cc.z);
		return hash1 ^ (hash2 << 1);
	}
};

class World
{
public:
	World(glm::vec3 camPos, unsigned int size, unsigned int program);
	~World();

	void renderWorld();
	void generateWorld();
	int getChunkAmount() { return this->chunks.size(); };
private:
	Chunk* getChunkAt(int x, int z);

	unsigned int shaderProgram;
	unsigned int worldSize;
	std::unordered_map<ChunkCoordinates, Chunk*, ChunkCoordinatesHash> chunks;
	glm::vec3 camPos;
};

#endif