#pragma once

#include "ChessPiece.h"

class Pawn : public ChessPiece {

public:
	Pawn(int ox, int oy, int ow, int oh, string team);
};

