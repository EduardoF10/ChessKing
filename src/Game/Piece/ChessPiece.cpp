#include "ChessPiece.h"
#include "../../Resources/Utils.h"

ChessPiece::ChessPiece(int xL, int yL, int xR, int yR, int w, int h, string team, string type) {
    this->leftX = xL;
    this->leftY = yL;
    this->rightX = xR;
    this->rightY = yR;
    this->width = w;
    this->height = h;
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

void ChessPiece::renderLeftBoard() {

}

void ChessPiece::renderRightBoard()
{
}

void ChessPiece::render() {

    this->spriteObj.draw(leftX, leftY, width, height);
    this->spriteObj.draw(rightX, rightY, width, height);


}

void ChessPiece::render(int ox, int oy) {
    this->spriteObj.draw(ox, oy, width, height);
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


