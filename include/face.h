#ifndef _FACE_H_
#define _FACE_H_

#include <glm/glm.hpp>
#include <unordered_map>
#include <block.h>

namespace FaceUtils
{
	inline constexpr int ATLAS_SIZE = 32;
	inline constexpr float TILE_SIZE = 16.0f / static_cast<float>(ATLAS_SIZE);

	enum class Direction
	{
		NORTH,
		SOUTH,
		EAST,
		WEST,
		TOP,
		BOTTOM,
		DIRECTION_COUNT
	};

	struct FacePositionData
	{
		glm::vec3 basePosition;
		glm::vec3 leftOffset;
		glm::vec3 rightOffset;
	};

	struct FaceUVData
	{
		float minX;
		float maxX;
		float minY;
		float maxY;
	};

	inline std::unordered_map<Direction, FacePositionData> positionData =
	{
		{
			Direction::NORTH,
			FacePositionData
			{
				glm::vec3{0.0f, 0.0f, 1.0f}, glm::vec3{0.0f, 1.0f, 0.0f}, glm::vec3{1.0f, 0.0f, 0.0f}
			}
		},
		{
			Direction::SOUTH,
			FacePositionData
			{	
				glm::vec3{1.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 1.0f, 0.0f}, glm::vec3{-1.0f, 0.0f, 0.0f}
			}
		},
		{
			Direction::EAST,
			FacePositionData
			{
				glm::vec3{1.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f}, glm::vec3{0.0f, 1.0f, 0.0f}
			}
		},
		{
			Direction::WEST,
			FacePositionData
			{
				glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 1.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f}
			}
		},
		{
			Direction::BOTTOM,
			FacePositionData
			{
				glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f}, glm::vec3{1.0f, 0.0f, 0.0f}
			}
		},
		{
			Direction::TOP,
			FacePositionData
			{
				glm::vec3{0.0f, 1.0f, 0.0f}, glm::vec3{1.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f}
			}
		},
	};

	inline FaceUVData getFaceUV(Direction dir, BlockUtils::Block block)
	{
		switch (dir)
		{
			case FaceUtils::Direction::TOP:
				return FaceUVData
				{
					static_cast<float>(block.topMinX) * TILE_SIZE,
					static_cast<float>(block.topMaxX) * TILE_SIZE,
					static_cast<float>(block.topMinY) * TILE_SIZE,
					static_cast<float>(block.topMaxY) * TILE_SIZE
				};
				break;
			case FaceUtils::Direction::BOTTOM:
				return FaceUVData
				{
					static_cast<float>(block.bottomMinX) * TILE_SIZE,
					static_cast<float>(block.bottomMaxX) * TILE_SIZE,
					static_cast<float>(block.bottomMinY) * TILE_SIZE,
					static_cast<float>(block.bottomMaxY) * TILE_SIZE
				};
				break;
			default:
				return FaceUVData
				{
					static_cast<float>(block.sideMinX) * TILE_SIZE,
					static_cast<float>(block.sideMaxX) * TILE_SIZE,
					static_cast<float>(block.sideMinY) * TILE_SIZE,
					static_cast<float>(block.sideMaxY) * TILE_SIZE
				};
				break;
		}
	};

	inline FacePositionData& getFacePostion(Direction dir)
	{
		return positionData.find(dir)->second;
	}
}
#endif