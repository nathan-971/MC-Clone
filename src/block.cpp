#include "block.h"

BlockUtils::Block::Block(char minX, char maxX, char minY, char maxY)
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
	char t_minX, char t_maxX, char t_minY, char t_maxY,
	char s_minX, char s_maxX, char s_minY, char s_maxY,
	char b_minX, char b_maxX, char b_minY, char b_maxY)
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