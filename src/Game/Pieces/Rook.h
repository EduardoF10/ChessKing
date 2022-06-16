#pragma once

#include "ChessPiece.h"
#include "../../Resources/Utils.h"

class Rook : public ChessPiece {

public:
	Rook(int ox, int oy, int ow, int oh, string team);
};