#include "BoardSquare.h"

BoardSquare::BoardSquare(ChessPiece* resident) {
	this->used = true;
	this->resident = resident;
}

BoardSquare::BoardSquare() {
	this->used = false;
	this->resident = 0;

}

void BoardSquare::setResident(ChessPiece* resident) {
	this->resident = resident;
	this->used = true;
}

void BoardSquare::setPieceCoordinates(int x, int y) {
	this->resident->setOX(x);
	this->resident->setOY(y);
}

void BoardSquare::clear() {
	this->used = false;
	this->resident = 0;
}

bool BoardSquare::inUse() {
	if (this->used == true) {
		return true;
	}
	return false;
}
