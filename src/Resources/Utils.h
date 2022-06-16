#pragma once

#include "ofMain.h"
#include "Sprites.h"
#include "../Game/Board/ChessBoard.h"

class Utils {

public:
	static ofImage getSprite(string name, string team);
	static ofImage getSprite(string name);
};

