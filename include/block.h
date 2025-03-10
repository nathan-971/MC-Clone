#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <vector>

namespace BlockUtils
{
	enum BlockType
	{
		AIR = 0,
		GRASS = 1,
		DIRT = 2,
		STONE = 3,
		COBBLESTONE = 4,
		PLANKS = 5,
		LOG = 6,
		GLASS = 7
	};

	class Block
	{
	public:
		char sideMinX, sideMaxX, sideMinY, sideMaxY;
		char bottomMinX, bottomMaxX, bottomMinY, bottomMaxY;
		char topMinX, topMaxX, topMinY, topMaxY;
		Block(char minX, char maxX, char minY, char maxY);
		Block(
			char tb_minX, char tb_maxX, char tb_minY, char tb_maxY,
			char s_minX, char s_maxX, char s_minY, char s_maxY
		);
		Block(
			char t_minX, char t_maxX, char t_minY, char t_maxY,
			char s_minX, char s_maxX, char s_minY, char s_maxY,
			char b_minX, char b_maxX, char b_minY, char b_maxY
		);
	};

	inline std::vector<Block> blockRegistry = {
		Block(0, 0, 0, 0), //AIR
		Block(0, 1, 0, 1,  //GRASS
			  0, 1, 1, 2,
			  2, 1, 1, 2),
		Block(2, 1, 1, 2), //DIRT
		Block(1, 2, 0, 1), //STONE
		Block(3, 3, 3, 3), //COBBLESTONE
		Block(4, 4, 4, 4), //PLANKS
		Block(5, 5, 5, 5,  //LOG
			  5, 5, 5, 5),
		Block(6, 6, 6, 6)  //GLASS
	};
}

#endif