#include "FluctSquare.h"


FluctSquare::FluctSquare(string boardPath) {
    this->opacity = 0;
    this->speed = 6;
    this->timer = 0;
    this->switcher = 0;
    this->boardImage.load(boardPath);
}


void FluctSquare::render(ChessPiece* selectedPiece, vector<vector<int>> squareLocations) {

    int OX = selectedPiece->getOX();
    int OY = selectedPiece->getOY();
    int OW = selectedPiece->getOW();
    int OH = selectedPiece->getOH();
    renderSelectionEffect(OX, OY, OW, OH);
    renderValidMoves(squareLocations, OW, OH);

    // Resetting the draw color after rendering the effect
    ofSetColor(255, 255, 255);

}


void FluctSquare::renderSelectionEffect(int ox, int oy, int ow, int oh) {

    // Obtaining the RGB values of a pixel in the tile where the chess piece is located
    ofColor colorTile = boardImage.getColor(ox, oy); 
    int redValue = (int)colorTile.r;
    int greenValue = (int)colorTile.g;
    int blueValue = (int)colorTile.b;

    // Setting the pulsating color and opacity
    ofSetColor(redValue, greenValue, blueValue, opacity);

    // Rendering the pulsating image
    ofDrawRectangle(ox, oy, ow, oh);

}


void FluctSquare::renderValidMoves(vector<vector<int>> squareLocations, int ow, int oh) {

    // Setting the pulsating color and opacity 
    ofSetColor(119, 198, 110, opacity);

    // Rendering the pulsating image for each tile with coordinates from squareLocations
    for (int i = 0; i < squareLocations.size(); i++) {
        ofDrawRectangle(squareLocations.at(i).at(0), squareLocations.at(i).at(1), ow, oh);
    }

}


void FluctSquare::tick() {

    // Opacity is increased if opacity is 0
    if (switcher == 0) {
        opacity += speed;
    }

    // Opacity is decreased if opacity is 1
    else {
        opacity -= speed;
    }

    // Timer is updated 
    timer += 1;

    // The switcher changes each time the cycle is completed and the timer resets to 0
    if (timer > 30) {
        switcher = !switcher;
        timer = 0;
    }

}


void FluctSquare::reset() {
    this->opacity = 0;
    this->timer = 0; 
    this->switcher = 0;
}
