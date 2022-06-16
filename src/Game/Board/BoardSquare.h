#pragma once

#include "../Pieces/ChessPiece.h"

class BoardSquare {

private:
	ChessPiece* resident;
	bool used;
	string id;

public:
	BoardSquare(ChessPiece* resident, string id);
	BoardSquare(string id);
	void setUse(bool used) { this->used = used; };
	void setResident(ChessPiece* resident) { this->resident = resident; };
	void removeResident() { this->resident = NULL; };
};

