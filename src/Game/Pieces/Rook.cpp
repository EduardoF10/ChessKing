#include "Rook.h"

Rook::Rook(int ox, int oy, int ow, int oh, string team) : ChessPiece(ox, oy, ow, oh, team) {
	this->spriteObj = Utils::getSprite("rook", team);
	this->possibleDirections = { "x0", "0x" };
	this->alive = true;
}
