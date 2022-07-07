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

void BoardSquare::setPieceCoordinates(int xL, int yL, int xR, int yR) {
	this->resident->setLX(xL);
	this->resident->setLY(yL);
	this->resident->setRX(xR);
	this->resident->setRY(yR);
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
