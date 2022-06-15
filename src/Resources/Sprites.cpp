#include "Sprites.h"

ofImage Sprites::getPawnSprite(string team) {
    ofImage temp;
    temp.load("images/pieces/" + team + ".png");
    temp.crop(640, 0, 128, 121);
    return temp;
}

ofImage Sprites::getBishopSprite(string team) {
    ofImage temp;
    temp.load("images/pieces/" + team + ".png");
    temp.crop(256, 0, 128, 121);
    return temp;
}

ofImage Sprites::getKnightSprite(string team) {
    ofImage temp;
    temp.load("images/pieces/" + team + ".png");
    temp.crop(384, 0, 128, 121);
    return temp;
}

ofImage Sprites::getRookSprite(string team) {
    ofImage temp;
    temp.load("images/pieces/" + team + ".png");
    temp.crop(512, 0, 128, 121);
    return temp;
}

ofImage Sprites::getQueenSprite(string team) {
    ofImage temp;
    temp.load("images/pieces/" + team + ".png");
    temp.crop(128, 0, 128, 121);
    return temp;
}

ofImage Sprites::getKingSprite(string team) {
    ofImage temp;
    temp.load("images/pieces/" + team + ".png");
    temp.crop(0, 0, 128, 121);
    return temp;
}

ofImage Sprites::getBoardSprite() {
    ofImage temp;
    temp.load("images/board/1.png");
    return temp;
}
