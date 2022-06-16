#include "BoardSquare.h"

BoardSquare::BoardSquare(ChessPiece* resident, string id) {
	this->used = TRUE;
	this->resident = resident;
	this->id = id;
}

BoardSquare::BoardSquare(string id) {
	this->used = FALSE;
	this->resident = NULL;
	this->id = id;

}
