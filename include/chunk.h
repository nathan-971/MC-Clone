#ifndef _CHUNK_H_
#define _CHUNK_H_

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <vector>
#include <unordered_map>

#include "face.h"
#include "block.h"

struct Vertex
{
	float x, y, z;
	float u, v;
	Vertex(float x, float y, float z, float u, float v)
	{
		//Vertex Position Data
		this->x = x;
		this->y = y;
		this->z = z;

		//Texcoord Data
		this->u = u;
		this->v = v;
	}

	Vertex(glm::vec3 vertexCoords, float u, float v)
	{
		//Vertex Position Data
		this->x = vertexCoords.x;
		this->y = vertexCoords.y;
		this->z = vertexCoords.z;

		//Texcoord Data
		this->u = u;
		this->v = v;
	}
};

enum ChunkNeighbours
{
	NORTH = 0,
	EAST = 1,
	SOUTH = 2,
	WEST = 3
};

class Chunk
{
public:
	Chunk(unsigned int size, unsigned int height, glm::vec3 pos);
	~Chunk();
	void generateChunk();
	void renderChunk(unsigned int& shaderID);
	Chunk* neighbours[4] = { nullptr };
	glm::vec3 chunkPos;
private:
	std::vector<unsigned int> generateChunkData(int chunkWidth, int chunkHeight);
	void addFace(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, FaceUtils::FacePositionData& pos, FaceUtils::FaceUVData uv,glm::vec3 currentCoordinates, FaceUtils::Direction dir, int& currentVertex);
	bool faceShouldRender(FaceUtils::Direction dir, std::vector<unsigned int>& chunkData, unsigned int& height, unsigned int& size, int curX, int curY, int curZ);
	bool chunkHasNeighbour(Chunk* neighbouringChunk);

	bool ready;
	bool generated;
	unsigned int VAO, VBO, EBO;
	unsigned int size;
	unsigned int height;

	std::vector<unsigned int> chunkData; //Holds enum vals for block types
	glm::vec3 worldPos;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
};

#endif