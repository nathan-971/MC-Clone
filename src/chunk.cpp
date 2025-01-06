#include "chunk.h"
#include <iostream>

Chunk::Chunk(unsigned int size, glm::vec3 pos)
{
	this->generated = false;
	this->ready = false;
	this->size = size;
	this->chunkPos = pos;
	genChunk();
}

Chunk::~Chunk()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);
}

void Chunk::genChunk()
{
	int currentVertex = 0;
	worldPos = glm::vec3(chunkPos.x * size, chunkPos.y * size, chunkPos.z * size);
    chunkData.resize(size * size * size, BlockUtils::BlockType::GRASS); //Fill with Block and reserve memory

    for (int x = 0; x < size; x++)
    {
        for (int z = 0; z < size; z++)
        {
            for (int y = 0; y < size; y++)
            {
                int index = x * size * size + z * size + y;
                if (chunkData[index] == BlockUtils::BlockType::AIR) // Skip if block is air
                {
                    continue;
                }

                const BlockUtils::Block* currentBlock = &BlockUtils::blockRegistry[chunkData[index]];

                // North Face
                if (z + 1 >= size || chunkData[x * size * size + (z + 1) * size + y] == BlockUtils::BlockType::AIR)
                {
                    vertices.push_back(Vertex(x + 0.0f, y + 0.0f, z + 1.0f, currentBlock->sideMinX, currentBlock->sideMinY));
                    vertices.push_back(Vertex(x + 0.0f, y + 1.0f, z + 1.0f, currentBlock->sideMinX, currentBlock->sideMaxY));
                    vertices.push_back(Vertex(x + 1.0f, y + 1.0f, z + 1.0f, currentBlock->sideMaxX, currentBlock->sideMaxY));
                    vertices.push_back(Vertex(x + 1.0f, y + 0.0f, z + 1.0f, currentBlock->sideMaxX, currentBlock->sideMinY));
                    indices.push_back(currentVertex + 0);
                    indices.push_back(currentVertex + 1);
                    indices.push_back(currentVertex + 2);
                    indices.push_back(currentVertex + 0);
                    indices.push_back(currentVertex + 2);
                    indices.push_back(currentVertex + 3);
                    currentVertex += 4;
                }

                // South Face
                if (z - 1 < 0 || chunkData[x * size * size + (z - 1) * size + y] == BlockUtils::BlockType::AIR)
                {
                    vertices.push_back(Vertex(x + 0.0f, y + 0.0f, z + 0.0f, currentBlock->sideMinX, currentBlock->sideMinY));
                    vertices.push_back(Vertex(x + 1.0f, y + 0.0f, z + 0.0f, currentBlock->sideMaxX, currentBlock->sideMinY));
                    vertices.push_back(Vertex(x + 1.0f, y + 1.0f, z + 0.0f, currentBlock->sideMaxX, currentBlock->sideMaxY));
                    vertices.push_back(Vertex(x + 0.0f, y + 1.0f, z + 0.0f, currentBlock->sideMinX, currentBlock->sideMaxY));
                    indices.push_back(currentVertex + 0);
                    indices.push_back(currentVertex + 1);
                    indices.push_back(currentVertex + 2);
                    indices.push_back(currentVertex + 0);
                    indices.push_back(currentVertex + 2);
                    indices.push_back(currentVertex + 3);
                    currentVertex += 4;
                }

                // West Face
                if (x - 1 < 0 || chunkData[(x - 1) * size * size + z * size + y] == BlockUtils::BlockType::AIR)
                {
                    vertices.push_back(Vertex(x + 0.0f, y + 0.0f, z + 0.0f, currentBlock->sideMinX, currentBlock->sideMinY));
                    vertices.push_back(Vertex(x + 0.0f, y + 1.0f, z + 0.0f, currentBlock->sideMinX, currentBlock->sideMaxY));
                    vertices.push_back(Vertex(x + 0.0f, y + 1.0f, z + 1.0f, currentBlock->sideMaxX, currentBlock->sideMaxY));
                    vertices.push_back(Vertex(x + 0.0f, y + 0.0f, z + 1.0f, currentBlock->sideMaxX, currentBlock->sideMinY));
                    indices.push_back(currentVertex + 0);
                    indices.push_back(currentVertex + 1);
                    indices.push_back(currentVertex + 2);
                    indices.push_back(currentVertex + 0);
                    indices.push_back(currentVertex + 2);
                    indices.push_back(currentVertex + 3);
                    currentVertex += 4;
                }

                // East Face
                if (x + 1 >= size || chunkData[(x + 1) * size * size + z * size + y] == BlockUtils::BlockType::AIR)
                {
                    vertices.push_back(Vertex(x + 1.0f, y + 0.0f, z + 0.0f, currentBlock->sideMinX, currentBlock->sideMinY));
                    vertices.push_back(Vertex(x + 1.0f, y + 0.0f, z + 1.0f, currentBlock->sideMaxX, currentBlock->sideMinY));
                    vertices.push_back(Vertex(x + 1.0f, y + 1.0f, z + 1.0f, currentBlock->sideMaxX, currentBlock->sideMaxY));
                    vertices.push_back(Vertex(x + 1.0f, y + 1.0f, z + 0.0f, currentBlock->sideMinX, currentBlock->sideMaxY));
                    indices.push_back(currentVertex + 0);
                    indices.push_back(currentVertex + 1);
                    indices.push_back(currentVertex + 2);
                    indices.push_back(currentVertex + 0);
                    indices.push_back(currentVertex + 2);
                    indices.push_back(currentVertex + 3);
                    currentVertex += 4;
                }

                // Bottom Face
                if (y - 1 < 0 || chunkData[x * size * size + z * size + (y - 1)] == BlockUtils::BlockType::AIR)
                {
                    vertices.push_back(Vertex(x + 0.0f, y + 0.0f, z + 0.0f, currentBlock->bottomMinX, currentBlock->bottomMinY));
                    vertices.push_back(Vertex(x + 1.0f, y + 0.0f, z + 0.0f, currentBlock->bottomMaxX, currentBlock->bottomMinY));
                    vertices.push_back(Vertex(x + 1.0f, y + 0.0f, z + 1.0f, currentBlock->bottomMaxX, currentBlock->bottomMaxY));
                    vertices.push_back(Vertex(x + 0.0f, y + 0.0f, z + 1.0f, currentBlock->bottomMinX, currentBlock->bottomMaxY));
                    indices.push_back(currentVertex + 0);
                    indices.push_back(currentVertex + 2);
                    indices.push_back(currentVertex + 1);
                    indices.push_back(currentVertex + 0);
                    indices.push_back(currentVertex + 3);
                    indices.push_back(currentVertex + 2);
                    currentVertex += 4;
                }

                // Top Face
                if (y + 1 >= size || chunkData[x * size * size + z * size + (y + 1)] == BlockUtils::BlockType::AIR)
                {
                    vertices.push_back(Vertex(x + 0.0f, y + 1.0f, z + 0.0f, currentBlock->topMinX, currentBlock->topMinY));
                    vertices.push_back(Vertex(x + 0.0f, y + 1.0f, z + 1.0f, currentBlock->topMinX, currentBlock->topMaxY));
                    vertices.push_back(Vertex(x + 1.0f, y + 1.0f, z + 1.0f, currentBlock->topMaxX, currentBlock->topMaxY));
                    vertices.push_back(Vertex(x + 1.0f, y + 1.0f, z + 0.0f, currentBlock->topMaxX, currentBlock->topMinY));
                    indices.push_back(currentVertex + 0);
                    indices.push_back(currentVertex + 2);
                    indices.push_back(currentVertex + 1);
                    indices.push_back(currentVertex + 0);
                    indices.push_back(currentVertex + 3);
                    indices.push_back(currentVertex + 2);
                    currentVertex += 4;
                }
            }
        }
    }

	this->generated = true;
	//std::cout << "Vertices Size: " << vertices.size() << "\nIndices Size: " << indices.size();
	//std::cout << "\nWorld Position: (" << chunkPos.x << ", " << chunkPos.y << ", " << chunkPos.z << ")\n";
}

void Chunk::renderChunk(unsigned int& shaderID)
{
	if (!ready)
	{
		if (generated)
		{
			glGenVertexArrays(1, &VAO);
			glBindVertexArray(VAO);

			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, x));
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, u));
			glEnableVertexAttribArray(1);

			glGenBuffers(1, &EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

			ready = true;
		}
	}

	glBindVertexArray(VAO);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, worldPos);
	glUniformMatrix4fv(glGetUniformLocation(shaderID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
}