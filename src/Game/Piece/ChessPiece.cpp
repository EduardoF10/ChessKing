#include "ChessPiece.h"
#include "../../Resources/Utils.h"

ChessPiece::ChessPiece(int ox, int oy, int ow, int oh, string team, string type) {
    this->ox = ox;
    this->oy = oy;
    this->ow = ow;
    this->oh = oh;
    this->team = team;
    this->selected = false;
    this->alive = true;
    this->type = type;

    // Setting the piece
    if (type == "pawn") {
        this->spriteObj = Utils::getSprite(team, "pawn");
        this->possibleDirections = { "01" };
    }
    else if (type == "rook") {
        this->spriteObj = Utils::getSprite(team, "rook");
        this->possibleDirections = { "x0", "0x" };
    }
    else if (type == "knight") {
        this->spriteObj = Utils::getSprite(team, "knight");
        this->possibleDirections = { "21", "12" };
    }
    else if (type == "bishop") {
        this->spriteObj = Utils::getSprite(team, "bishop");
        this->possibleDirections = { "xx" };
    }
    else if (type == "queen") {
        this->spriteObj = Utils::getSprite(team, "queen");
        this->possibleDirections = { "x0", "0x", "xx" };
    }
    else if (type == "king") {
        this->spriteObj = Utils::getSprite(team, "king");
        this->possibleDirections = { "10", "01", "11" };
    }
}

void ChessPiece::render() {

    this->spriteObj.draw(ox, oy, ow, oh);

}

void ChessPiece::render(int ox, int oy) {
    this->spriteObj.draw(ox, oy, ow, oh);
}

bool ChessPiece::sameTeam(string team) {
    if (this == NULL) {
        return false;
    }
    if (this->team == team) {
        return true;
    }
    else {
        return false;
    }
}


