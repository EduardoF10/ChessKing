#pragma once

#include "ofMain.h"
#include "../Game/Board/ChessBoard.h"


/**
* Contains useful methods that help implement the proyect
*/
class Utils {

public:

	/**
	* Returns an image of the chess piece
	*
	* @param team - The team color of the chess piece
	* @param type - The type of piece that is wanted
	* @return An ofImage of the chess piece with its appropiate color
	*/
	static ofImage getSprite(string team, string type);


	/**
	* Returns a chess tile coordinate
	*
	* @param x The x-coordinate of the mouse when it clicked
	* @param y The y-coordinate of the mouse when it clicked
	*
	* @return A vector that contains the row and column value of the chess tile that was clicked and an 
	* additional value that indicates on which board it is on (left 0 right 1)
	*/
	static vector<int> getTileCoordinate(int x, int y);


	/**
	* Returns the absolute value of an integer
	* 
	* @param x - The integer that will be processed
	* @return The absolute value of x
	*/
	static int absInt(int x);

	static int invertX(int x);


	static int invertY(int Y);
};

