#include "Queen.h"

Queen::Queen(int ox, int oy, int ow, int oh, string team) : ChessPiece(ox, oy, ow, oh, team) {
	this->spriteObj = Utils::getSprite("queen", team);
	this->possibleDirections = { "x0", "0x", "xx" };
	this->alive = true;
}
