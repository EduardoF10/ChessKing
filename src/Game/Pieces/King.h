#pragma once

#include "ChessPiece.h"

class King : public ChessPiece {

public:
	King(int ox, int oy, int ow, int oh, string team);
};