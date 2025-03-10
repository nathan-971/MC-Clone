#include "block.h"

BlockUtils::Block::Block(char minX, char maxX, char minY, char maxY) //Single Textured Block
{
	sideMinX = minX;
	sideMaxX = maxX;
	sideMinY = minY;
	sideMaxY = maxY;

	bottomMinX = minX;
	bottomMaxX = maxX;
	bottomMinY = minY;
	bottomMaxY = maxY;

	topMinX = minX;
	topMaxX = maxX;
	topMinY = minY;
	topMaxY = maxY;
}

BlockUtils::Block::Block(
	char tb_minX, char tb_maxX, char tb_minY, char tb_maxY,
	char s_minX, char s_maxX, char s_minY, char s_maxY) //Double Textured Block
{
	topMinX = tb_minX;
	topMaxX = tb_maxX;
	topMinY = tb_minY;
	topMaxY = tb_maxY;

	sideMinX = s_minX;
	sideMaxX = s_maxX;
	sideMinY = s_minY;
	sideMaxY = s_maxY;

	bottomMinX = tb_minX;
	bottomMaxX = tb_maxX;
	bottomMinY = tb_minY;
	bottomMaxY = tb_maxY;
}

BlockUtils::Block::Block(
	char t_minX, char t_maxX, char t_minY, char t_maxY,
	char s_minX, char s_maxX, char s_minY, char s_maxY,
	char b_minX, char b_maxX, char b_minY, char b_maxY) //Triple Textured Block
{
	topMinX = t_minX;
	topMaxX = t_maxX;
	topMinY = t_minY;
	topMaxY = t_maxY;

	sideMinX = s_minX;
	sideMaxX = s_maxX;
	sideMinY = s_minY;
	sideMaxY = s_maxY;

	bottomMinX = b_minX;
	bottomMaxX = b_maxX;
	bottomMinY = b_minY;
	bottomMaxY = b_maxY;
}