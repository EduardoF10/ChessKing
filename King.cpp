#include "King.h"

King::King(int ox, int oy, int ow, int oh, string team) : ChessPiece(ox, oy, ow, oh, team) {
	this->overworldSprite = Utils::getSprite("king", team);
	this->possibleDirections = { "10", "01", "11"};
	this->alive = true;
}
