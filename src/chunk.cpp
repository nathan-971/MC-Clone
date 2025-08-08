#include "chunk.h"
#include <iostream>

Chunk::Chunk(unsigned int size, unsigned int height, glm::vec3 pos)
{
	this->generated = false;
	this->ready = false;
	this->size = size;
    this->height = height;
	this->chunkPos = pos;
}

Chunk::~Chunk()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);
}

void Chunk::generateChunk()
{
	worldPos = glm::vec3(chunkPos.x * size, chunkPos.y * size, chunkPos.z * size);
    chunkData = generateChunkData(size, height);

    int currentVertex = 0;
    for (int y = 0; y < height; y++)
    {
        for (int z = 0; z < size; z++)
        {
            for (int x = 0; x < size; x++)
            {
                int index = y * size * size + z * size + x;
                if (chunkData[index] == BlockUtils::BlockType::AIR)
                {
                    continue;
                }

                const BlockUtils::Block* currentBlock = &BlockUtils::blockRegistry[chunkData[index]];
                for (int i = 0; i < static_cast<int>(FaceUtils::Direction::DIRECTION_COUNT); ++i) 
                {
                    FaceUtils::Direction direction = static_cast<FaceUtils::Direction>(i);

                    if (faceShouldRender(direction, chunkData, height, size, x, y, z))
                    {
                        addFace(
                            vertices,
                            indices,
                            FaceUtils::getFacePostion(direction),
                            FaceUtils::getFaceUV(direction, *currentBlock),
                            glm::vec3(x, y, z),
                            direction,
                            currentVertex
                        );
                    }
                }
            }
        }
    }
	this->generated = true;
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

void Chunk::addFace(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, FaceUtils::FacePositionData& pos, FaceUtils::FaceUVData uv, glm::vec3 currentCoordinates, FaceUtils::Direction dir, int& currentVertex)
{
    glm::vec3 base = pos.basePosition + currentCoordinates;
    if (dir == FaceUtils::Direction::EAST) //Temporary Fix For Incorrect UV
    {
        vertices.push_back(Vertex(base, uv.maxX, uv.minY));
        vertices.push_back(Vertex(base + pos.leftOffset, uv.minX, uv.minY));
        vertices.push_back(Vertex(base + pos.leftOffset + pos.rightOffset, uv.minX, uv.maxY));
        vertices.push_back(Vertex(base + pos.rightOffset, uv.maxX, uv.maxY));
    }
    else
    {
        vertices.push_back(Vertex(base, uv.minX, uv.minY));
        vertices.push_back(Vertex(base + pos.leftOffset, uv.minX, uv.maxY));
        vertices.push_back(Vertex(base + pos.leftOffset + pos.rightOffset, uv.maxX, uv.maxY));
        vertices.push_back(Vertex(base + pos.rightOffset, uv.maxX, uv.minY));
    }

    indices.push_back(currentVertex + 0);
    indices.push_back(currentVertex + 1);
    indices.push_back(currentVertex + 2);
    indices.push_back(currentVertex + 0);
    indices.push_back(currentVertex + 2);
    indices.push_back(currentVertex + 3);
    currentVertex += 4;
}

bool Chunk::faceShouldRender(FaceUtils::Direction dir, std::vector<unsigned int>& chunkData, unsigned int& height, unsigned int& size, int curX, int curY, int curZ)
{
    switch (dir)
    {
        case FaceUtils::Direction::NORTH:
            return curZ + 1 >= size || chunkData[curY * (size * size) + (curZ + 1) * size + curX] == BlockUtils::BlockType::AIR;
        case FaceUtils::Direction::SOUTH:
            return curZ - 1 < 0 || chunkData[curY * (size * size) + (curZ - 1) * size + curX] == BlockUtils::BlockType::AIR;
        case FaceUtils::Direction::WEST:
            return curX - 1 < 0 || chunkData[curY * (size * size) + curZ * size + (curX - 1)] == BlockUtils::BlockType::AIR;
        case FaceUtils::Direction::EAST:
            return curX + 1 >= size || chunkData[curY * (size * size) + curZ * size + (curX + 1)] == BlockUtils::BlockType::AIR;
        case FaceUtils::Direction::TOP:
            return curY + 1 >= height || chunkData[(curY + 1) * size * size + curZ * size + curX] == BlockUtils::BlockType::AIR;
        case FaceUtils::Direction::BOTTOM:
            return curY - 1 < 0 || chunkData[(curY - 1) * size * size + curZ * size + curX] == BlockUtils::BlockType::AIR;
        default:
            return false;
    }
}

bool Chunk::chunkHasNeighbour(Chunk* neighbouringChunk)
{
    if (neighbouringChunk == nullptr)
    {
        return false;
    }
    return true;
}

std::vector<unsigned int> Chunk::generateChunkData(int chunkWidth, int chunkHeight)
{
    std::vector<unsigned int> newData;
    newData.reserve(chunkWidth * chunkWidth * chunkHeight);
    for (int y = 0; y < chunkHeight; y++)
    {
        for (int z = 0; z < chunkWidth; z++)
        {
            for (int x = 0; x < chunkWidth; x++)
            {
                if (y <= 16)
                {
                    newData.push_back(BlockUtils::BlockType::STONE);
                }
                else if (y >= 17 && y <= 30)
                {
                    newData.push_back(BlockUtils::BlockType::DIRT);
                }
                else if (y == 31)
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