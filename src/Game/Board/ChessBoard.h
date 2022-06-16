#pragma once

#include "BoardSquare.h"
#include "../Pieces/ChessPiece.h"
#include "../Pieces/Bishop.h"
#include "../Pieces/Rook.h"
#include "../Pieces/Pawn.h"
#include "../Pieces/Knight.h"
#include "../Pieces/Queen.h"
#include "../Pieces/King.h"

class ChessBoard {
private:
	BoardSquare* boardSquares[8][8];
	ofImage boardSprite;
	vector<ChessPiece*> player1Pieces;
	vector<ChessPiece*> player2Pieces;
	void setBoard(string player1);

public:
	ChessBoard(string player1);
	void render();
};

