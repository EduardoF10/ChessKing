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


vector<int> Utils::getTileCoordinate(int x, int y) {
    int rightBoardStartX = (1019.0 / 1920.0) * ofGetWindowWidth();

    int row = -1;
    int col = -1;

    if (x < rightBoardStartX) {


        // Finding col
        if (x < 128) {
            col = 0;
        }
        else if (x < 256) {
            col = 1;
        }
        else if (x < 384) {
            col = 2;
        }
        else if (x < 512) {
            col = 3;
        }
        else if (x < 640) {
            col = 4;
        }
        else if (x < 768) {
            col = 5;
        }
        else if (x < 896) {
            col = 6;
        }
        else if (x < 1024) {
            col = 7;
        }
        else {
            col = 8;
        }

        // Finding row
        if (y < 121) {
            row = 7;
        }
        else if (y < 242) {
            row = 6;
        }
        else if (y < 363) {
            row = 5;
        }
        else if (y < 484) {
            row = 4;
        }
        else if (y < 605) {
            row = 3;
        }
        else if (y < 726) {
            row = 2;
        }
        else if (y < 847) {
            row = 1;
        }
        else if (y < 968) {
            row = 0;
        }
        else {
            row = 8;
        }

    }
    else {

    }

    

    vector<int> result = { row, col };

    return result;
}


int Utils::absInt(int x) {
    if (x < 0) {
        return -1 * x;
    }
    else {
        return x;
    }
}

