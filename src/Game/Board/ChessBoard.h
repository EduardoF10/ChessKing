#pragma once

#include "BoardSquare.h"
#include "../Piece/ChessPiece.h"
#include "../../Resources/FluctSquare.h"
#include "../Player/Player.h"

/**
* Implements all the activities done in a game of chess
*/
class ChessBoard {

private:

	BoardSquare* boardSquares[8][8];  // The grid of chess tiles

	FluctSquare* fluctile;  // An object that enables fluctuating effect

	ofImage boardSprite;  // The image of the chess board

	vector<ChessPiece*> player1Pieces;  // Vector of playable chess pieces for player 1

	vector<ChessPiece*> player2Pieces;  // Vector of playable chess pieces for player 2

	bool fluctEnabled;  // Enables or disables the fluctuating effect

	Player* currentPlayer;  // Indicates the player that must play in the current turn

	Player* nextPlayer;  // Indicates the player that must play next turn

	ChessPiece* activePiece;  // Indicates the chess piece that was selected

	bool moveEnabled;  // Enables or disables a move from being played

	vector<vector<int>> validMoves;  // Contains all the valid moves from the piece that was selected

	vector<int> moveDestination;  // Contains the coordinates of the tile that the selected piece will move to

	vector<float> moveSpeed;  // The speed at which the piece will move

	int moveCounter;  // Counts how many frames the piece has moved

	bool clickEnabled;  // Enables or disables the selection of a chess piece

	int boardTurn;  // Indicates which side of the board has the turn (left 0 right 1)

	int tileWidth, tileHeight;  // The size of the screen will be measured using these tile dimensions

	bool dragMoveEnabled;  // Indicates if a dragged move is in effect



	/**
	* Sets the board to play the game
	*
	* @param player1 - The team color of player 1
	*/
	void setBoard(string player1);




public:

	// @param player1 - The player that will play the game
	ChessBoard(string player1);


	// @return The FluctSquare object from this class (fluctile)
	FluctSquare* getFluct() { return this->fluctile; };


	// @return The chessboard image in use
	ofImage getBoardImage() { return this->boardSprite; };


	/**
	* @param piece - A chess piece
	* @return A copy of a chess piece
	*/
	ChessPiece* getPieceCopy(ChessPiece* piece);


	/**
	* Sets the active piece that is selected from the board
	*
	* @param activePiece - The chess piece that was selected
	*/
	void setActivePiece(ChessPiece* piece) { this->activePiece = piece; };


	/**
	* Sets the properties of the chess move that will take place
	*
	* @param row - The row where the piece will end up
	* @param col - The column where the piece will end up
	* @param moveToken - The type of move
	*/
	void setMove(int row, int col, int moveToken);


	// Renders the current state of the chess board
	void render();


	/**
	* Performs the appropiate activity after clicking on the board
	* 
	* @param x - The x coordinate of the mouse when it clicked
	* @param y - The y coordinate of the mouse when it clicked
	*/
	void onClick(int x, int y);


	// Updates the properties of the fluctile 
	void tick();


	/**
	* Checks whether a valid move was selected on the board
	* 
	* @param x - The x coordinate of the mouse when it clicked
	* @param y - The y coordinate of the mouse when it clicked
	*/
	bool clickedValidMove(int x, int y);


	/**
	* Renders the move selected by the player on the specified board
	* 
	* @param leftBoard - Specifies if the move will be rendered on the left board (show 1 no show 0)
	* @param rightBoard - Specifies if the move will be rendered on the right board (show 1 no show 0)
	*/
	void renderMove(int leftBoard, int rightBoard);


	// Renders the active piece on the coordinates of the mouse pointer
	void renderDrag();


	/**
	* Hides the rendering of a chess piece
	* 
	* @param piece - The piece that will disappear
	* @param boardTurn - Indicates which side of the board we are on
	*/
	void hidePiece(ChessPiece* piece, int boardTurn);



	/**
	* Returns the valid moves that the player can make with the selected piece
	*
	* @param team - The team color of the selected piece
	* @param direction - The direction in which the piece can go
	* @param ox - The x coordinate of the chess piece
	* @param oy - The y coordinate of the chess piece
	* @param ow - The width distance of the chess piece
	* @param oh - The height distance of the chess piece
	* @return - A vector of coordinates that the piece can go to
	*/
	vector<vector<int>> ChessBoard::getValidMoves(string team, string direction, int ox, int oy, int ow, int oh);



	/**
	* Returns a chess tile coordinate
	*
	* @param x The x-coordinate of the mouse when it clicked
	* @param y The y-coordinate of the mouse when it clicked
	*
	* @return A vector that contains the row and column value of the chess tile that was clicked and an
	* additional value that indicates on which board it is on (left 0 right 1)
	*/
	vector<int> getTileCoordinate(int x, int y);

	/**
	* 
	* 
	* @param row - The row where the chess tile is located
	* @param col - The column where the chess tile is located
	* @param boardTurn - The side of the board that we want to look on
	* @return The x and y coordinate of a chess tile
	*/
	vector<int> getCoordinateFromTile(int row, int col, int boardTurn);

	/**
	* Executes the process after dropping a piece
	* 
	* @param x - The x coordinate of the mouse after releasing it
	* @param y - The y coordinate of the mouse after releasing it
	*/
	void placedPiece(int x, int y);

	// Reset piece selection
	void resetSelection();

};

