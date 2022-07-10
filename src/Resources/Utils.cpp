#include "Utils.h"



constexpr auto HEIGHT_CONSTANT = 10;


ofImage Utils::getSprite(string team, string type) {

    // The group of pieces with the appropiate color is loaded
    ofImage temp;
    temp.load("images/pieces/" + team + ".png");


    // The piece with the selected type is taken
    if (type == "pawn") {
        temp.crop(640, 0, 128, 121);
    }
    else if (type == "bishop") {
        temp.crop(256, 0, 128, 121);
    }
    else if (type == "knight") {
        temp.crop(384, 0, 128, 121);
    }
    else if (type == "rook") {
        temp.crop(512, 0, 128, 121);
    }
    else if (type == "queen") {
        temp.crop(128, 0, 128, 121);
    }
    else {
        temp.crop(0, 0, 128, 121);
    }
    return temp;
}


int Utils::absInt(int x) {
    if (x < 0) {
        return -1 * x;
    }
    else {
        return x;
    }
}

