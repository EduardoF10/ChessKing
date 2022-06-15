#include "Bishop.h"

Bishop::Bishop(int ox, int oy, int ow, int oh, string team) : ChessPiece(ox, oy, ow, oh, team) {
	this->overworldSprite = Utils::getSprite("bishop", team);
	this->possibleDirections = {"xx"};
	this->alive = true;
}
