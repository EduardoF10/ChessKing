#include "Utils.h"

ofImage Utils::getSprite(string name, string team) {
    if (name == "pawn") {
        return Sprites::getPawnSprite(team);
    }
    else if (name == "bishop") {
        return Sprites::getBishopSprite(team);
    }
    else if (name == "knight") {
        return Sprites::getKnightSprite(team);
    }
    else if (name == "rook") {
        return Sprites::getRookSprite(team);
    }
    else if (name == "queen") {
        return Sprites::getQueenSprite(team);
    }
    else if (name == "king") {
        return Sprites::getKingSprite(team);
    }
}

ofImage Utils::getSprite(string name) {
    if (name == "board") {
        return Sprites::getBoardSprite();
    }
}

