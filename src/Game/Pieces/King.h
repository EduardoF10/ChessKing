#pragma once

#include "ChessPiece.h"
#include "../../Resources/Utils.h"

class King : public ChessPiece {

private:
	string type;

public:
	King(int ox, int oy, int ow, int oh, string team);
};