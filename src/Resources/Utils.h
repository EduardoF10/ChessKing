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
	* Returns the absolute value of an integer
	* 
	* @param x - The integer that will be processed
	* @return The absolute value of x
	*/
	static int absInt(int x);
};

