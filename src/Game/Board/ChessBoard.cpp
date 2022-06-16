#include "ChessBoard.h"

ChessBoard::ChessBoard(string player1) {
	setBoard(player1);

}


void ChessBoard::setBoard(string player1) {

	this->boardSprite.load("images/board/1.png");

	// Setting up the pieces
	player1Pieces = {};

	// First row
	ChessPiece* rook1 = new Rook(0, 847, 128, 121, player1);
	ChessPiece* rook2 = new Rook(896, 847, 128, 121, player1);
	ChessPiece* knight1 = new Knight(128, 847, 128, 121, player1);
	ChessPiece* knight2 = new Knight(768, 847, 128, 121, player1);
	ChessPiece* bishop1 = new Bishop(256, 847, 128, 121, player1);
	ChessPiece* bishop2 = new Bishop(640, 847, 128, 121, player1);
	ChessPiece* queen = new Queen(384, 847, 128, 121, player1);
	ChessPiece* king = new King(512, 847, 128, 121, player1);
	BoardSquare* bs00 = new BoardSquare(rook1, "00");
	BoardSquare* bs01 = new BoardSquare(knight1, "01");
	BoardSquare* bs02 = new BoardSquare(bishop1, "02");
	BoardSquare* bs03 = new BoardSquare(queen, "03");
	BoardSquare* bs04 = new BoardSquare(king, "04");
	BoardSquare* bs05 = new BoardSquare(bishop2, "05");
	BoardSquare* bs06 = new BoardSquare(knight2, "06");
	BoardSquare* bs07 = new BoardSquare(rook2, "07");
	this->boardSquares[0][0] = bs00;
	this->boardSquares[0][1] = bs01;
	this->boardSquares[0][2] = bs02;
	this->boardSquares[0][3] = bs03;
	this->boardSquares[0][4] = bs04;
	this->boardSquares[0][5] = bs05;
	this->boardSquares[0][6] = bs06;
	this->boardSquares[0][7] = bs07;
	player1Pieces.push_back(rook1);
	player1Pieces.push_back(rook2);
	player1Pieces.push_back(knight1);
	player1Pieces.push_back(knight2);
	player1Pieces.push_back(bishop1);
	player1Pieces.push_back(bishop2);
	player1Pieces.push_back(queen);
	player1Pieces.push_back(king);


	// Second row
	for (int i = 0; i < 8; i++) {
		string id = "1" + to_string(i);
		ChessPiece* pawn = new Pawn(i * 128, 726, 128, 121, player1);
		BoardSquare* bsq = new BoardSquare(pawn, id);
		this->boardSquares[1][i] = bsq;
		player1Pieces.push_back(pawn);
	}

	// Subsequent rows
	for (int row = 2; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			string id = to_string(row) + to_string(col);
			BoardSquare* bsq = new BoardSquare(id);
			this->boardSquares[row][col];
		}
	}
}

void ChessBoard::render() {
	this->boardSprite.draw(0, 0);
	for (int i = 0; i < player1Pieces.size(); i++) {
		player1Pieces.at(i)->render();
	}
}
