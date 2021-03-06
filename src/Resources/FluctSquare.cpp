#include "FluctSquare.h"


FluctSquare::FluctSquare(string boardPath) {
    this->opacity = 0;
    this->speed = 6;
    this->timer = 0;
    this->switcher = 0;
    this->boardImage.load(boardPath);
}


void FluctSquare::render(ChessPiece* selectedPiece, vector<vector<int>> squareLocations, int boardTurn) {
    
    // The selected piece coordiantes and dimensions are obtained
    int OX, OY;
    if (boardTurn == 0) {
        OX = selectedPiece->getLX();
        OY = selectedPiece->getLY();
    }
    else {
        OX = selectedPiece->getRX();
        OY = selectedPiece->getRY();
    }
    int width = selectedPiece->getW();
    int height = selectedPiece->getH();

    // Rendering the effects
    renderSelectionEffect(OX, OY, width, height);
    renderValidMoves(squareLocations, width, height);

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
    ofSetColor(119, 198, 110, 100 + opacity);

    // Rendering the pulsating image for each tile on the left board
    for (int i = 0; i < squareLocations.size(); i++) {
        //ofDrawRectangle(squareLocations.at(i).at(0), squareLocations.at(i).at(1), ow, oh);
        ofDrawCircle(squareLocations.at(i).at(0) + (ow / 2), squareLocations.at(i).at(1) + (oh / 2), (oh / 4));
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
