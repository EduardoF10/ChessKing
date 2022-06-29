#pragma once

#include "ofMain.h"
#include "../Piece/ChessPiece.h"

/**
* Implements each user in the game
*/
class Player {

private:

	string team;  // The team color of the player's pieces

	bool myTurn;  // The value that indicates if it's the player's turn (No 0 Yes 1)

public:

	/**
	* Constructor
	* 
	* @param team - The team color of the player's pieces
	* @param myTurn - The value that indicates if it's the player's turn (No 0 Yes 1)
	*/
	Player(string team, bool myTurn);


	/**
	* @return True if it's the player's turn and false otherwise
	*/
	bool isMyTurn() { return myTurn; };


	/**
	* @return The player's team color
	*/
	string getTeam() { return team; };
};

