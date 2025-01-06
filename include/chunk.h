#ifndef _CHUNK_H_
#define _CHUNK_H_

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <vector>

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
};

class Chunk
{
public:
	Chunk(unsigned int size, glm::vec3 pos);
	~Chunk();
	void genChunk();
	void renderChunk(unsigned int& shaderID);
	glm::vec3 chunkPos;
	std::vector<unsigned int> chunkData; //Holds enum vals for block types
private:
	bool ready;
	bool generated;
	unsigned int VAO, VBO, EBO;
	unsigned int size;

	glm::vec3 worldPos;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
};

#endif