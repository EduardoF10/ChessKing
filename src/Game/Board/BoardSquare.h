#pragma once

#include "../Piece/ChessPiece.h"

/**
* Implements the functions of a chess tile
*/
class BoardSquare {

private:

	ChessPiece* resident;  // The chess piece located in this BoardSquare

	bool used;  // True if the piece is present in the tile and false if absent


public:
	
	// @param resident - The chess piece that will go into this tile
	BoardSquare(ChessPiece* resident);

	BoardSquare();

	/**
	* Sets the resident in the chess tile
	* 
	* @param - resident - The chess piece that will go into this tile
	*/
	void setResident(ChessPiece* resident);


	/**
	* Sets the coordinates for the piece in this tile
	* 
	* @param xL - The x coordinates for the chess piece in the left board
	* @param xR - The x coordinates for the chess piece in the right board
	* @param yL - The y coordinates for the chess piece in the left board
	* @param yR - The y coordinates for the chess piece in the right board
	*/
	void setPieceCoordinates(int xL, int yL, int xR, int yR);


	// @return The chess piece located in this tile
	ChessPiece* getResident() { return this->resident; };

	// Clears the contents in this object
	void clear();

	// Checks if a piece is present in the tile
	bool inUse();
};

