#pragma once

#include "ChessPiece.h"
#include "../../Resources/Utils.h"

class Queen : public ChessPiece {

public:
	Queen(int ox, int oy, int ow, int oh, string team);
};