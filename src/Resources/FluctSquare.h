#pragma once

#include "ofMain.h"
#include "../Game/Piece/ChessPiece.h"


/**
* Implements the effects that take part after selecting a Chess piece
*/
class FluctSquare {

private:

	int speed;  // The rate at which the opacity changes per frame

	int opacity;  // The opacity value of each fluctuating square on the chess board

	int timer; // Counts how many frames have passed 

	bool switcher;  // The on and off value that determines if the opacity increases or decreases

	ofImage boardImage; // The image of the board where the effect will take place


	/**
	* It renders a pulsating effect on the selected piece
	* 
	* @param ox - The x coordinate in pixels of the upper left corner of the tile where the selected piece is located
	* @param oy - The y coordinate in pixels of the upper left corner of the tile where the selected piece is located
	* @param ow - The width distance in pixels of a tile
	* @param oh - The height distance in pixels of a tile
	*/
	void renderSelectionEffect(int ox, int oy, int ow, int oh);


	/**
	* It renders a pulsating effect on each tile where the selected piece can move
	*
	* @param squareLocations - All the x and y coordinates of the available tiles where it can move
	* @param ow - The width distance in pixels of each tile
	* @param oh - The height distance in pixels of each tile
	*/
	void renderValidMoves(vector<vector<int>> squareLocations, int ow, int oh);


public:

	/**
	* Sets the properties to their starting position
	* 
	* @param boardPath - A string path that will be loaded as an ofImage for the image of the board
	*/
	FluctSquare(string boardPath);


	/**
	* It renders the complete effect after selecting a piece on the board
	* 
	* @param selectedPiece - The piece that was clicked on the board
	* @param squareLocations - All the x and y coordinates of the available tiles where it can move
	*/
	void render(ChessPiece* selectedPiece, vector<vector<int>> squareLocations);


	// Updates the properties of the pulsating effect
	void tick();


	// Resets the properties of the pulsating effect to their default values
	void reset();

};

