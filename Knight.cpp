#include "Knight.h"

Knight::Knight(int ox, int oy, int ow, int oh, string team) : ChessPiece(ox, oy, ow, oh, team) {
	this->overworldSprite = Utils::getSprite("knight", team);
	this->possibleDirections = { "31", "13" };
	this->alive = true;
}
