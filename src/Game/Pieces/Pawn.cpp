#include "Pawn.h"

Pawn::Pawn(int ox, int oy, int ow, int oh, string team) : ChessPiece(ox, oy, ow, oh, team) {
	this->overworldSprite = Utils::getSprite("pawn", team);
	this->possibleDirections = { "10", "01" };
	this->alive = true;
}
