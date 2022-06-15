#include "ChessPiece.h"

ChessPiece::ChessPiece(int ox, int oy, int ow, int oh, string team) {
    this->ox = ox;
    this->oy = oy;
    this->ow = ow;
    this->oh = oh;
    this->team = team;
}

void ChessPiece::renderOverworld() {
    overworldSprite.draw(ox, oy, ow, oh);
}