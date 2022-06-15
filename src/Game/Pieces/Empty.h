#pragma once

#include "ChessPiece.h"

class Empty : public ChessPiece {

public:
	Empty(int ox, int oy, int ow, int oh, string team);
};
