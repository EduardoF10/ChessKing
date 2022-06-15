#pragma once

#include "ofMain.h"
#include "Utils.h"

class ChessPiece {
protected:
    // Overworld Coordinates and dimensions
    int ox, oy, ow, oh;
    ofImage overworldSprite;
    vector<string> possibleDirections;
    string team;
    bool alive;

public:
    ChessPiece(int ox, int oy, int ow, int oh, string team);
    void renderOverworld();
    int getOX() { return ox; };
    int getOY() { return oy; };
    int getOW() { return ow; };
    int getOH() { return oh; };
    void setOX(int ox) { this->ox = ox; };
    void setOY(int oy) { this->oy = oy; };
    void setOW(int ow) { this->ow = ow; };
    void setOH(int oh) { this->oh = oh; };
    bool isAlive() { return alive; };
    void kill() { this->alive = false; };
};

