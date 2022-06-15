#pragma once

#include "ChessPiece.h"

class BoardSquare {

private:
	ChessPiece* resident;
	bool used;
	string id;
};

