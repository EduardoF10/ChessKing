#include "ChessBoard.h"
#include "../../Resources/Utils.h"
#include <algorithm>


#define HORIZONTAL_MOVE 0
#define VERTICAL_MOVE 1
#define DIAGONAL_MOVE 2
#define HORIZONTAL_HORSE_MOVE 3
#define VERTICAL_HORSE_MOVE 4

constexpr auto WIDTH_CONSTANT = (12.0 / 106.0) + 18;
constexpr auto HEIGHT_CONSTANT = 10;


ChessBoard::ChessBoard(string player1) {
	setBoard(player1);

}


void ChessBoard::setBoard(string player1) {

	// Initializing the properties
	this->tileWidth = 106.0;
	this->tileHeight = 108.0;
	this->boardTurn = 0;
	this->activePiece = 0;
	this->clickEnabled = true;
	this->moveEnabled = false;
	this->boardSprite.load("images/board/dual1.png");
	this->fluctile = new FluctSquare("images/board/dual1.png");
	this->fluctEnabled = false;
	this->validMoves = {};
	this->moveDestination = {};
	this->moveSpeed = {};
	Player* redPlayer = new Player("blue", true);
	this->currentPlayer = redPlayer;
	this->player1Pieces = {};
	this->dragMoveEnabled = false;

	// Filling the first row of the board
	ChessPiece* rook1 = new ChessPiece(53, 864, 1761, 108, 106, 108, player1, "rook");
	ChessPiece* knight1 = new ChessPiece(159, 864, 1655, 108, 106, 108, player1, "knight");
	ChessPiece* bishop1 = new ChessPiece(265, 864, 1549, 108, 106, 108, player1, "bishop");
	ChessPiece* queen = new ChessPiece(371, 864, 1443, 108, 106, 108, player1, "queen");
	ChessPiece* king = new ChessPiece(477, 864, 1337, 108, 106, 108, player1, "king");
	ChessPiece* bishop2 = new ChessPiece(583, 864, 1231, 108, 106, 108, player1, "bishop");
	ChessPiece* knight2 = new ChessPiece(689, 864, 1125, 108, 106, 108, player1, "knight");
	ChessPiece* rook2 = new ChessPiece(795, 864, 1019, 108, 106, 108, player1, "rook");


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
		ChessPiece* pawn = new ChessPiece(53 + (i * 106), 756, 1019 + ((7 - i) * 106), 216, 106, 108, player1, "pawn");
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
		this->fluctile->render(activePiece, validMoves, boardTurn);
		this->fluctile->tick();
		ofSetColor(255, 255, 255);
	}
	if (moveEnabled == true) {
		if (dragMoveEnabled == true) {
			if (boardTurn == 0) {
				renderMove(0, 1);
			}
			else {
				renderMove(1, 0);
			}
		}
		else {
			renderMove(1, 1);
		}
	}
}

void ChessBoard::onClick(int x, int y) {

	if (clickEnabled == false) {
		return;
	}

	// Getting the coordinates of the tile that was clicked
	vector<int> tileLocation = getTileCoordinate(x, y);

	// Check if out of bounds
	if (tileLocation.at(0) == -1 || tileLocation.at(1) == -1) {
		return;
	}
	
	// Return if wrong side of the board was clicked
	if (tileLocation.at(2) != boardTurn) {
		return;
	}
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
		vector<int> activeTile = getTileCoordinate(activePiece->getLX(), activePiece->getLY());
		if (row == activeTile.at(0) && col == activeTile.at(1)) {
			resetSelection();
			this->activePiece = NULL;
			return;
		}

	}

	// If the player clicked on one of his pieces
	if (boardSquares[row][col]->getResident()->sameTeam(currentPlayer->getTeam())) {
		this->validMoves.clear();

		// Setting the active piece
		this->activePiece = getPieceCopy(boardSquares[row][col]->getResident());

		// Getting the active piece coordinates depending on the side of the board
		int xCoordinate, yCoordinate;
		if (boardTurn == 0) {
			xCoordinate = activePiece->getLX();
			yCoordinate = activePiece->getLY();
		}
		else {
			xCoordinate = activePiece->getRX();
			yCoordinate = activePiece->getRY();
		}
		int pieceWidth = activePiece->getW();
		int pieceHeight = activePiece->getH();

		// Getting the valid moves for each possible direction
		for (int i = 0; i < activePiece->getDirections().size(); i++) {
			vector<vector<int>> possibleMoves = getValidMoves(activePiece->getTeam(), activePiece->getDirections().at(i), xCoordinate, yCoordinate, pieceWidth, pieceHeight);
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


void ChessBoard::renderMove(int leftBoard, int rightBoard) {
	vector<int> tileLoc = {};
	if (boardTurn == 0) {
		tileLoc = getTileCoordinate(activePiece->getLX(), activePiece->getLY());
	}
	else {
		tileLoc = getTileCoordinate(activePiece->getRX(), activePiece->getRY());
	}
	int row = tileLoc.at(0);
	int col = tileLoc.at(1);
	int residentLX = boardSquares[row][col]->getResident()->getLX();
	int residentRX = boardSquares[row][col]->getResident()->getRX();
	int residentLY = boardSquares[row][col]->getResident()->getLY();
	int residentRY = boardSquares[row][col]->getResident()->getRY();

	// When the move cycle has ended
	if (this->moveCounter == 0) {
		boardSquares[row][col]->setPieceCoordinates(moveDestination.at(0), moveDestination.at(1), moveDestination.at(2), moveDestination.at(3));
		vector<int> currentTile = getTileCoordinate(moveDestination.at(0), moveDestination.at(1));
		ChessPiece* movedPiece = boardSquares[row][col]->getResident();
		boardSquares[row][col]->clear();

		// Updating the tile where the piece moved into
		boardSquares[currentTile.at(0)][currentTile.at(1)]->setResident(movedPiece);

		this->moveEnabled = false;
		this->clickEnabled = true;
		this->activePiece = NULL;
		this->dragMoveEnabled = false;
		moveDestination.clear();
		moveSpeed.clear();
		return;
	}
	else {
		// Updating the coordinates of the moving chess piece
		boardSquares[row][col]->setPieceCoordinates(residentLX + ((int) moveSpeed.at(0) * leftBoard), residentLY + ((int) moveSpeed.at(1) * leftBoard), residentRX + ((int) moveSpeed.at(2)* rightBoard), residentRY + ((int) moveSpeed.at(3) * rightBoard));
		this->moveCounter--;
	}
}

void ChessBoard::renderDrag() {

	if (activePiece == NULL) {
		return;
	}

	hidePiece(activePiece, boardTurn);
	int x = ofGetMouseX();
	int y = ofGetMouseY();
	int startX = x - (tileWidth / 2);
	int startY = y - (tileHeight / 2);
	this->activePiece->render(startX, startY);
	

}

void ChessBoard::hidePiece(ChessPiece* piece, int boardTurn) {

	int x, y;

	if (boardTurn == 0) {
		x = piece->getLX();
		y = piece->getLY();
	}
	else {
		x = piece->getRX();
		y = piece->getRY();
	}

	// Obtaining the RGB values of a pixel in the tile where the chess piece is located
	ofColor colorTile = boardSprite.getColor(x, y);
	int redValue = (int)colorTile.r;
	int greenValue = (int)colorTile.g;
	int blueValue = (int)colorTile.b;

	// Setting the tile color
	ofSetColor(redValue, greenValue, blueValue);

	// Rendering the tile
	ofDrawRectangle(x, y, tileWidth, tileHeight);

	// Cleaning color
	ofSetColor(255, 255, 255);
}


void ChessBoard::setMove(int row, int col, int moveToken) {
	vector<int> leftCoordinates = getCoordinateFromTile(row, col, 0);
	vector<int> rightCoordinates = getCoordinateFromTile(row, col, 1);
	this->moveDestination = { leftCoordinates.at(0), leftCoordinates.at(1), rightCoordinates.at(0), rightCoordinates.at(1) };

	int xDiff = leftCoordinates.at(0) - activePiece->getLX();
	int yDiff = leftCoordinates.at(1) - activePiece->getLY();
	int xDiffPos = Utils::absInt(xDiff);
	int yDiffPos = Utils::absInt(yDiff);

	// Max amount of tiles traveled in one of the axis
	int counter = max(xDiffPos / tileWidth, yDiffPos / tileHeight);

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
		this->moveSpeed = { 21.2f * xSign, 0, -21.2f * xSign, 0};
	}
	// Vertical moves
	else if (moveToken == VERTICAL_MOVE) {
		this->moveSpeed = { 0, 21.6f * ySign, 0, -21.6f * ySign};
	}
	// Diagonal moves
	else if (moveToken == DIAGONAL_MOVE) {
		this->moveSpeed = { 17.6f * xSign, 18.0f * ySign, -17.6f * xSign, -18.0f * ySign };
		this->moveCounter = counter * 6;
	}
	// Horse move long horizontal
	else if (moveToken == HORIZONTAL_HORSE_MOVE) {
		this->moveSpeed = { 21.2f * xSign, 10.8f * ySign, -21.2f * xSign, -10.8f * ySign};
	}
	// Horse move long vertical
	else {
		this->moveSpeed = { 10.6f * xSign, 21.6f * ySign, -10.6f * xSign, -21.6f * ySign };
	}
}


bool ChessBoard::clickedValidMove(int x, int y) {
	vector<int> clickedTile = getTileCoordinate(x, y);

	// Getting tile coordinates
	vector<int> coordinates = getCoordinateFromTile(clickedTile.at(0), clickedTile.at(1), clickedTile.at(2));
	int tileX = coordinates.at(0);
	int tileY = coordinates.at(1);

	// Verifying if a valid move tile was clicked
	for (int i = 0; i < validMoves.size(); i++) {
		if ((validMoves.at(i).at(0) == tileX && validMoves.at(i).at(1) == tileY)) {
			setMove(clickedTile.at(0), clickedTile.at(1), validMoves.at(i).at(2));
			return true;
		}
	}
	return false;

}


ChessPiece* ChessBoard::getPieceCopy(ChessPiece* piece) {
	int xL = piece->getLX();
	int xR = piece->getRX();
	int yL = piece->getLY();
	int yR = piece->getRY();
	int width = piece->getW();
	int height = piece->getH();
	string team = piece->getTeam();
	string type = piece->getType();
	ChessPiece* result = new ChessPiece(xL, yL, xR, yR, width, height, team, type);
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
			coor = getTileCoordinate(ox, oy - oh);
			if (boardSquares[coor.at(0)][coor.at(1)] == NULL || !boardSquares[coor.at(0)][coor.at(1)]->getResident()->sameTeam(team)) {
				vector<int> move1 = { ox, oy - oh, VERTICAL_MOVE };
				directions.push_back(move1);

				// If the pawn is at starting position
				if (boardTurn == 0 && oy == tileHeight * 7) {
					coor = getTileCoordinate(ox, tileHeight * 5);
					if (boardSquares[coor.at(0)][coor.at(1)] == NULL || !boardSquares[coor.at(0)][coor.at(1)]->getResident()->sameTeam(team)) {
						vector<int> move2 = { ox, (int) tileHeight * 5, VERTICAL_MOVE };
						directions.push_back(move2);
					}
				}
			}
		}
		return directions;
	}

	int rightBoardStartX = tileWidth * ((12.0 / 106.0) + 9.5);
	int boardEnd = ofGetWindowWidth() - (tileWidth / 2);

	if (dirX != 72 && dirY != 72) {
		for (int i = 0; i < 2; i++) {
			newOX = ox + (dirX * ow * multX);
			multX *= -1;
			// Check if the square is bounded in the region
			if ((newOX < tileWidth / 2) || ((newOX >= tileWidth * 8.5) && (newOX < rightBoardStartX)) || (newOX >= boardEnd)) {
				continue;
			}
			for (int j = 0; j < 2; j++) {
				newOY = oy + (dirY * oh * multY);
				multY *= -1;
				// Check if the square is bounded in the region
				if (newOY < tileHeight || newOY > tileHeight * 8) {
					continue;
				}
				coor = getTileCoordinate(newOX, newOY);
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
		while (newOY < tileHeight * 8) {
			newOY += oh;
			coor = getTileCoordinate(ox, newOY);
			if (boardSquares[coor.at(0)][coor.at(1)] == NULL || !boardSquares[coor.at(0)][coor.at(1)]->getResident()->sameTeam(team)) {
				directions.push_back({ ox, newOY, VERTICAL_MOVE });
			}
			else {
				break;
			}
		}
		newOY = oy;
		while (newOY > tileHeight) {
			newOY -= oh;
			coor = getTileCoordinate(ox, newOY);
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
		while (newOX < tileWidth * 7.5 && newOX < boardEnd - tileWidth) {
			newOX += ow;
			coor = getTileCoordinate(newOX, oy);
			if (boardSquares[coor.at(0)][coor.at(1)] == NULL || !boardSquares[coor.at(0)][coor.at(1)]->getResident()->sameTeam(team)) {
				directions.push_back({ newOX, oy, HORIZONTAL_MOVE });
			}
			else {
				break;
			}
		}
		newOX = ox;
		while (newOX > tileWidth / 2) {
			newOX -= ow;
			coor = getTileCoordinate(newOX, oy);
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
		while (newOX < tileWidth * 7.5 && newOX < boardEnd - tileWidth) {
			newOX += ow;
			if (newPosY < tileHeight * 8 && upY == true) {
				newPosY += oh;
				coor = getTileCoordinate(newOX, newPosY);
				if (boardSquares[coor.at(0)][coor.at(1)] == NULL || !boardSquares[coor.at(0)][coor.at(1)]->getResident()->sameTeam(team)) {
					directions.push_back({ newOX, newPosY, DIAGONAL_MOVE });
				}
				else {
					upY = false;
				}
			}
			if (newNegY > tileHeight && downY == true) {
				newNegY -= oh;
				coor = getTileCoordinate(newOX, newNegY);
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
		while (newOX > tileWidth / 2) {
			newOX -= ow;
			if (newPosY < tileHeight * 8 && upY == true) {
				newPosY += oh;
				coor = getTileCoordinate(newOX, newPosY);
				if (boardSquares[coor.at(0)][coor.at(1)] == NULL || !boardSquares[coor.at(0)][coor.at(1)]->getResident()->sameTeam(team)) {
					directions.push_back({ newOX, newPosY, DIAGONAL_MOVE });
				}
				else {
					upY = false;
				}
			}
			if (newNegY > tileHeight && downY == true) {
				newNegY -= oh;
				coor = getTileCoordinate(newOX, newNegY);
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


vector<int> ChessBoard::getTileCoordinate(int x, int y) {

	int rightBoardStartX = tileWidth * ((12.0 / 106.0) + 9.5);
	int row = -1;
	int col = -1;


	// The column depends on the which side of the board the piece is on
	if (x < rightBoardStartX) {

		// Finding row
		for (int i = 0; i < 8; i++) {
			if (y < ((tileHeight * 2) + (tileHeight * i))) {
				row = 7 - i;
				break;
			}
		}

		// Finding col
		for (int i = 0; i < 8; i++) {
			if (x < ((tileWidth / 2) + tileWidth + (tileWidth * i))) {
				col = i;
				break;
			}
		}

		vector<int> result = { row, col, 0 };
		return result;

	}
	else {

		// Finding row
		for (int i = 0; i < 8; i++) {
			if (y < ((tileHeight * 2) + (tileHeight * i))) {
				row = i;
				break;
			}
		}

		// Finding col
		for (int i = 0; i < 8; i++) {
			if (x < (rightBoardStartX + tileWidth + (tileWidth * i))) {
				col = 7 - i;
				break;
			}
		}

		vector<int> result = { row, col, 1 };
		return result;

	}

}


vector<int> ChessBoard::getCoordinateFromTile(int row, int col, int boardTurn) {

	int x, y;
	vector<int> result;

	if (boardTurn == 0) {
		x = (tileWidth / 2) + (col * tileWidth);
		y = ofGetWindowHeight() - (tileHeight * 2) - (row * tileHeight);
		result = { x, y };
	}
	else {
		int rightBoardStartX = tileWidth * ((12.0 / 106.0) + 9.5);
		x = rightBoardStartX + ((7 - col) * tileWidth);
		y = tileHeight + (tileHeight * row);
		result = { x, y };
	}


	return result;
}

void ChessBoard::placedPiece(int x, int y) {

	// If a piece wasn't selected
	if (activePiece == NULL) {
		return;
	}

	// If the piece was dropped on a valid move tile
	if (clickedValidMove(x, y)) {
		this->moveEnabled = true;
		this->dragMoveEnabled = true;
		this->clickEnabled = false;

		vector<int> tileLoc = getTileCoordinate(x, y);
		vector<int> tileCoor = getCoordinateFromTile(tileLoc.at(0), tileLoc.at(1), boardTurn);

		// The piece is set on the board it was dropped
		vector<int> previousTile = getTileCoordinate(activePiece->getLX(), activePiece->getLY());
		if (boardTurn == 0) {
			boardSquares[previousTile.at(0)][previousTile.at(1)]->setPieceCoordinates(moveDestination.at(0), moveDestination.at(1), activePiece->getRX(), activePiece->getRY());
		}
		else {
			boardSquares[previousTile.at(0)][previousTile.at(1)]->setPieceCoordinates(activePiece->getLX(), activePiece->getLY(), moveDestination.at(2), moveDestination.at(3));
		}

	}
	else {
		this->clickEnabled = true;
		this->validMoves.clear();
		this->activePiece = NULL;
	}
	this->fluctEnabled = false;
}

void ChessBoard::resetSelection() {
	 
	this->fluctile->reset();
	this->fluctEnabled = false;
	this->validMoves.clear();

}


