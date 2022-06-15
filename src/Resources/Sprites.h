#pragma once

# include "ofMain.h"

class Sprites {

public:
	static ofImage getPawnSprite(string team);
	static ofImage getBishopSprite(string team);
	static ofImage getKnightSprite(string team);
	static ofImage getRookSprite(string team);
	static ofImage getQueenSprite(string team);
	static ofImage getKingSprite(string team);
	static ofImage getBoardSprite();
};

