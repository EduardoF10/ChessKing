#include "ChessBoard.h"
#include "../../Resources/Utils.h"
#include <algorithm>


#define HORIZONTAL_MOVE 0
#define VERTICAL_MOVE 1
#define DIAGONAL_MOVE 2
#define HORIZONTAL_HORSE_MOVE 3
#define VERTICAL_HORSE_MOVE 4


ChessBoard::ChessBoard(string player1) {
	setBoard(player1);

}


void ChessBoard::setBoard(string player1) {

	// Initializing the properties
	this->activePiece = 0;
	this->clickEnabled = true;
	this->moveEnabled = false;
	this->boardSprite.load("images/board/2.png");
	this->fluctile = new FluctSquare("images/board/2.png");
	this->fluctEnabled = false;
	this->validMoves = {};
	this->moveDestination = {};
	this->moveSpeed = {};
	Player* redPlayer = new Player("red", true);
	this->currentPlayer = redPlayer;
	this->player1Pieces = {};

	// Filling the first row of the board
	ChessPiece* rook1 = new ChessPiece(0, 847, 128, 121, player1, "rook");
	ChessPiece* rook2 = new ChessPiece(896, 847, 128, 121, player1, "rook");
	ChessPiece* knight1 = new ChessPiece(128, 847, 128, 121, player1, "knight");
	ChessPiece* knight2 = new ChessPiece(768, 847, 128, 121, player1, "knight");
	ChessPiece* bishop1 = new ChessPiece(256, 847, 128, 121, player1, "bishop");
	ChessPiece* bishop2 = new ChessPiece(640, 847, 128, 121, player1, "bishop");
	ChessPiece* queen = new ChessPiece(384, 847, 128, 121, player1, "queen");
	ChessPiece* king = new ChessPiece(512, 847, 128, 121, player1, "king");
	BoardSquare* bs00 = new BoardSquare(rook1);
	BoardSquare* bs01 = new BoardSquare(knight1);
	BoardSquare* bs02 = new BoardSquare(bishop1);
	BoardSquare* bs03 = new BoardSquare(queen);
	BoardSquare* bs04 = new BoardSquare(king);
	BoardSquare* bs05 = new BoardSquare(bishop2);
	BoardSquare* bs06 = new BoardSquare(knight2);
	BoardSquare* bs07 = new BoardSquare(rook2);
	this->boardSquares[0][0] = bs00;
	this->boardSquares[0][1] = bs01;
	this->boardSquares[0][2] = bs02;
	this->boardSquares[0][3] = bs03;
	this->boardSquares[0][4] = bs04;
	this->boardSquares[0][5] = bs05;
	this->boardSquares[0][6] = bs06;
	this->boardSquares[0][7] = bs07;

	// Updating the pieces of player 1
	player1Pieces.push_back(rook1);
	player1Pieces.push_back(rook2);
	player1Pieces.push_back(knight1);
	player1Pieces.push_back(knight2);
	player1Pieces.push_back(bishop1);
	player1Pieces.push_back(bishop2);
	player1Pieces.push_back(queen);
	player1Pieces.push_back(king);


	// Filling the second row of the board and updating the pieces of player1
	for (int i = 0; i < 8; i++) {
		ChessPiece* pawn = new ChessPiece(i * 128, 726, 128, 121, player1, "pawn");
		BoardSquare* bsq = new BoardSquare(pawn);
		this->boardSquares[1][i] = bsq;
		player1Pieces.push_back(pawn);
	}

	// Filling empty squares for the subsequent rows
	for (int row = 2; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			BoardSquare* bsq = new BoardSquare();
			this->boardSquares[row][col] = bsq;
		}
	}
}

void ChessBoard::render() {
	this->boardSprite.draw(0, 0);
	// Rendering each piece from player 1 in the board
	for (int i = 0; i < player1Pieces.size(); i++) {
		player1Pieces.at(i)->render();
	}
	if (fluctEnabled) {
		this->fluctile->render(activePiece, validMoves);
		this->fluctile->tick();
		ofSetColor(255, 255, 255);
	}
	if (moveEnabled == true) {
		renderMove();
	}
}

void ChessBoard::onClick(int x, int y) {

	// Getting the coordinates of the tile that was clicked
	vector<int> tileLocation = Utils::getTileCoordinate(x, y);
	int row = tileLocation.at(0);
	int col = tileLocation.at(1);

	// If a piece with valid moves was previously selected
	if (!validMoves.empty()) {
		if (clickedValidMove(x, y)) {
			this->fluctEnabled = false;
			this->moveEnabled = true;
			this->clickEnabled = false;
			this->validMoves.clear();
			return;
		}
	}

	// If the same piece was clicked, selection resets
	if (activePiece != NULL) {
		vector<int> activeTile = Utils::getTileCoordinate(activePiece->getOX(), activePiece->getOY());
		if (row == activeTile.at(0) && col == activeTile.at(1)) {
			this->fluctile->reset();
			this->fluctEnabled = false;
			this->activePiece = NULL;
			this->validMoves.clear();
			return;
		}

	}

	// If the player clicked on an empty tile or out of bounds
	if (row == 8 || col == 8 || !boardSquares[row][col]->inUse()) {
		return;
	}

	// If the player clicked on one of his pieces
	else if (boardSquares[row][col]->getResident()->sameTeam(currentPlayer->getTeam())) {
		this->validMoves.clear();

		// Setting the active piece
		this->activePiece = getPieceCopy(boardSquares[row][col]->getResident());

		// Getting the active piece coordinates
		int OX = activePiece->getOX();
		int OY = activePiece->getOY();
		int OW = activePiece->getOW();
		int OH = activePiece->getOH();

		// Getting the valid moves for each possible direction
		for (int i = 0; i < activePiece->getDirections().size(); i++) {
			vector<vector<int>> possibleMoves = getValidMoves(activePiece->getTeam(), activePiece->getDirections().at(i), OX, OY, OW, OH);
			for (int j = 0; j < possibleMoves.size(); j++) {
				validMoves.push_back(possibleMoves.at(j));
			}
		}

		this->fluctile->reset();
		this->fluctEnabled = true;
	}

}

void ChessBoard::tick() {
	fluctile->tick();
}



void ChessBoard::renderMove() {
	vector<int> tileLoc = Utils::getTileCoordinate(activePiece->getOX(), activePiece->getOY());
	int row = tileLoc.at(0);
	int col = tileLoc.at(1);
	int residentX = boardSquares[row][col]->getResident()->getOX();
	int residentY = boardSquares[row][col]->getResident()->getOY();

	// When the move cycle has ended
	if (this->moveCounter == 0) {
		boardSquares[row][col]->setPieceCoordinates(moveDestination.at(0), moveDestination.at(1));
		vector<int> currentTile = Utils::getTileCoordinate(moveDestination.at(0), moveDestination.at(1));
		ChessPiece* movedPiece = boardSquares[row][col]->getResident();
		boardSquares[row][col]->clear();

		// Updating the tile where the piece moved into
		boardSquares[currentTile.at(0)][currentTile.at(1)]->setResident(movedPiece);

		this->moveEnabled = false;
		this->clickEnabled = true;
		this->activePiece = NULL;
		return;
	}
	else {
		// Updating the coordinates of the moving chess piece
		boardSquares[row][col]->setPieceCoordinates(residentX + (int) moveSpeed.at(0), residentY + (int) moveSpeed.at(1));
		this->moveCounter--;
	}
}

void ChessBoard::setMove(int xGoal, int yGoal, int moveToken) {
	this->moveDestination = { xGoal, yGoal };
	int xDiff = xGoal - activePiece->getOX();
	int yDiff = yGoal - activePiece->getOY();
	int xDiffPos = Utils::absInt(xDiff);
	int yDiffPos = Utils::absInt(yDiff);

	// Max amount of tiles traveled in one of the axis
	int counter = max(xDiffPos / 128, yDiffPos / 121);

	this->moveCounter = counter * 5;

	// Determining right or left and up or down directions
	float xSign, ySign;
	if (xDiff < 0) {
		xSign = -1.0;
	}
	else {
		xSign = 1.0;
	}
	if (yDiff < 0) {
		ySign = -1.0;
	}
	else {
		ySign = 1.0;
	}

	// Horizontal moves
	if (moveToken == HORIZONTAL_MOVE) {
		this->moveSpeed = { 25.6f * xSign, 0};
	}
	// Vertical moves
	else if (moveToken == VERTICAL_MOVE) {
		this->moveSpeed = { 0, 24.2f * ySign};
	}
	// Diagonal moves
	else if (moveToken == DIAGONAL_MOVE) {
		this->moveSpeed = { 21.3f * xSign, 20.2f * ySign };
		this->moveCounter = counter * 6;
	}
	// Horse move long horizontal
	else if (moveToken == HORIZONTAL_HORSE_MOVE) {
		this->moveSpeed = { 25.6f * xSign, 12.1f * ySign};
	}
	// Horse move long vertical
	else {
		this->moveSpeed = { 12.8f * xSign, 24.2f * ySign};
	}
}


bool ChessBoard::clickedValidMove(int x, int y) {
	vector<int> clickedTile = Utils::getTileCoordinate(x, y);

	// Getting tile coordinates
	int tileX = clickedTile.at(1) * 128;
	int tileY = 847 - (121 * clickedTile.at(0));

	// Verifying if a valid move tile was clicked
	for (int i = 0; i < validMoves.size(); i++) {
		if (validMoves.at(i).at(0) == tileX && validMoves.at(i).at(1) == tileY) {
			setMove(tileX, tileY, validMoves.at(i).at(2));
			return true;
		}
	}
	return false;

}

ChessPiece* ChessBoard::getPieceCopy(ChessPiece* piece) {
	int ox = piece->getOX();
	int oy = piece->getOY();
	int ow = piece->getOW();
	int oh = piece->getOH();
	string team = piece->getTeam();
	string type = piece->getType();
	ChessPiece* result = new ChessPiece(ox, oy, ow, oh, team, type);
	return result;
}



vector<vector<int>> ChessBoard::getValidMoves(string team, string direction, int ox, int oy, int ow, int oh) {

	// Integer values of direction
	int dirX = direction[0] - '0';
	int dirY = direction[1] - '0';

	// Direction values (down or right 1 && up or left -1)
	int multX = 1;
	int multY = 1;

	int newOX = 0;
	int newOY = 0;
	vector<vector<int>> directions = {};
	vector<int> coor;

	// If it's a pawn
	vector<string> pawnDir = { "01" };
	if (activePiece->getDirections() == pawnDir) {
		if (oy > 0) {
			coor = Utils::getTileCoordinate(ox, oy - oh);
			if (boardSquares[coor.at(0)][coor.at(1)] == NULL || !boardSquares[coor.at(0)][coor.at(1)]->getResident()->sameTeam(team)) {
				vector<int> move1 = { ox, oy - oh, VERTICAL_MOVE };
				directions.push_back(move1);

				// If the pawn is at starting position
				if (oy == 726) {
					coor = Utils::getTileCoordinate(ox, 484);
					if (boardSquares[coor.at(0)][coor.at(1)] == NULL || !boardSquares[coor.at(0)][coor.at(1)]->getResident()->sameTeam(team)) {
						vector<int> move2 = { ox, 484, VERTICAL_MOVE };
						directions.push_back(move2);
					}
				}
			}
		}
		return directions;
	}
	if (dirX != 72 && dirY != 72) {
		for (int i = 0; i < 2; i++) {
			newOX = ox + (dirX * ow * multX);
			multX *= -1;
			// Check if the square is bounded in the region
			if (newOX > 896 || newOX < 0) {
				continue;
			}
			for (int j = 0; j < 2; j++) {
				newOY = oy + (dirY * oh * multY);
				multY *= -1;
				// Check if the square is bounded in the region
				if (newOY > 847 || newOY < 0) {
					continue;
				}
				coor = Utils::getTileCoordinate(newOX, newOY);
				if (boardSquares[coor.at(0)][coor.at(1)] == NULL || !boardSquares[coor.at(0)][coor.at(1)]->getResident()->sameTeam(team)) {
					// If it's a knight
					vector<string> knightDir = { "21", "12" };
					if (activePiece->getDirections() == knightDir) {
						// If it's long horizontal
						if (Utils::absInt(newOX - ox) > Utils::absInt(newOY - oy)) {
							directions.push_back({ newOX, newOY, HORIZONTAL_HORSE_MOVE });
						}
						// If it's long vertical
						else {
							directions.push_back({ newOX, newOY, VERTICAL_HORSE_MOVE });
						}
					}
					// If it's a king 
					else {
						// If diagonal move
						if (newOX != ox && newOY != oy) {
							directions.push_back({ newOX, newOY, DIAGONAL_MOVE });
						}
						// If horizontal move
						else if (newOY == oy) {
							directions.push_back({ newOX, newOY, HORIZONTAL_MOVE });
						}
						else {
							// If vertical move
							directions.push_back({ newOX, newOY, VERTICAL_MOVE });
						}

					}
				}
			}
		}
	}
	// "0x" scenario
	else if (dirX == 0) {
		newOY = oy;
		while (newOY < 847) {
			newOY += oh;
			coor = Utils::getTileCoordinate(ox, newOY);
			if (boardSquares[coor.at(0)][coor.at(1)] == NULL || !boardSquares[coor.at(0)][coor.at(1)]->getResident()->sameTeam(team)) {
				directions.push_back({ ox, newOY, VERTICAL_MOVE });
			}
			else {
				break;
			}
		}
		newOY = oy;
		while (newOY > 0) {
			newOY -= oh;
			coor = Utils::getTileCoordinate(ox, newOY);
			if (boardSquares[coor.at(0)][coor.at(1)] == NULL || !boardSquares[coor.at(0)][coor.at(1)]->getResident()->sameTeam(team)) {
				directions.push_back({ ox, newOY, VERTICAL_MOVE });
			}
			else {
				break;
			}
		}
	}
	// "x0" scenario
	else if (dirY == 0) {
		newOX = ox;
		while (newOX < 896) {
			newOX += ow;
			coor = Utils::getTileCoordinate(newOX, oy);
			if (boardSquares[coor.at(0)][coor.at(1)] == NULL || !boardSquares[coor.at(0)][coor.at(1)]->getResident()->sameTeam(team)) {
				directions.push_back({ newOX, oy, HORIZONTAL_MOVE });
			}
			else {
				break;
			}
		}
		newOX = ox;
		while (newOX > 0) {
			newOX -= ow;
			coor = Utils::getTileCoordinate(newOX, oy);
			if (boardSquares[coor.at(0)][coor.at(1)] == NULL || !boardSquares[coor.at(0)][coor.at(1)]->getResident()->sameTeam(team)) {
				directions.push_back({ newOX, oy, HORIZONTAL_MOVE });
			}
			else {
				break;
			}
		}
	}
	// "xx" scenraio
	else {
		bool upY = true;
		bool downY = true;
		newOX = ox;
		int newPosY = oy;
		int newNegY = oy;
		while (newOX < 896) {
			newOX += ow;
			if (newPosY < 847 && upY == true) {
				newPosY += oh;
				coor = Utils::getTileCoordinate(newOX, newPosY);
				if (boardSquares[coor.at(0)][coor.at(1)] == NULL || !boardSquares[coor.at(0)][coor.at(1)]->getResident()->sameTeam(team)) {
					directions.push_back({ newOX, newPosY, DIAGONAL_MOVE });
				}
				else {
					upY = false;
				}
			}
			if (newNegY > 0 && downY == true) {
				newNegY -= oh;
				coor = Utils::getTileCoordinate(newOX, newNegY);
				if (boardSquares[coor.at(0)][coor.at(1)] == NULL || !boardSquares[coor.at(0)][coor.at(1)]->getResident()->sameTeam(team)) {
					directions.push_back({ newOX, newNegY, DIAGONAL_MOVE });
				}
				else {
					downY = false;
				}
			}
		}
		upY = true;
		downY = true;
		newOX = ox;
		newPosY = oy;
		newNegY = oy;
		while (newOX > 0) {
			newOX -= ow;
			if (newPosY < 847 && upY == true) {
				newPosY += oh;
				coor = Utils::getTileCoordinate(newOX, newPosY);
				if (boardSquares[coor.at(0)][coor.at(1)] == NULL || !boardSquares[coor.at(0)][coor.at(1)]->getResident()->sameTeam(team)) {
					directions.push_back({ newOX, newPosY, DIAGONAL_MOVE });
				}
				else {
					upY = false;
				}
			}
			if (newNegY > 0 && downY == true) {
				newNegY -= oh;
				coor = Utils::getTileCoordinate(newOX, newNegY);
				if (boardSquares[coor.at(0)][coor.at(1)] == NULL || !boardSquares[coor.at(0)][coor.at(1)]->getResident()->sameTeam(team)) {
					directions.push_back({ newOX, newNegY, DIAGONAL_MOVE });
				}
				else {
					downY = false;
				}
			}

		}
	}
	
	return directions;
}


