#pragma once

#include "ofMain.h"

/**
* Implements every aspect of a chess piece
*/
class ChessPiece {

private:

    double leftX, leftY;  // Coordinates in the left board

    double rightX, rightY; // Coordinates in the right board

    double width, height; // Dimensions

    ofImage spriteObj;  // Chess piece image

    vector<string> possibleDirections;  // Vector of strings that represent the type of moves it can make

    string team;  // Team color of the chess piece

    bool alive;  // The life state of the chess piece

    bool selected;  // Indicates if the piece was selected

    string type;  // The type of chess piece


public:

    /**
    * Constructor
    * 
    * @param xL - The x coordinate of the chess piece in the left board
    * @param yL - The y coordinate of the chess piece in the left board
    * @param xR - The x coordinate of the chess piece in the right board
    * @param yR - The y coordinate of the chess piece in the right board
    * @param w - The width of the chess piece
    * @param h - The height of the chess piece
    * @param team - The team color of the chess piece
    * @param type - The type of chess piece (pawn, bishop, knight, ...)
    */
    ChessPiece(int xL, int yL, int xR, int yR, int w, int h, string team, string type);


    // @return The x coordinate of the chess piece in the left board
    int getLX() { return leftX; };

    // @return The x coordinate of the chess piece in the right board
    int getRX() { return rightX; }

    // @return The y coordinate of the chess piece in the left board
    int getLY() { return leftY; };

    // @return The y coordinate of the chess piece in the right board
    int getRY() { return rightY; }

    // @return The width of the chess piece
    int getW() { return width; };

    // @return The height of the chess piece
    int getH() { return height; };


    // Sets coordinates and dimensions
    void setLX(int x) { this->leftX = x; };
    // Sets coordinates and dimensions
    void setRX(int x) { this->rightX = x; };
    // Sets coordinates and dimensions
    void setLY(int y) { this->leftY = y; };
    // Sets coordinates and dimensions
    void setRY(int y) { this->rightY = y; };
    // Sets coordinates and dimensions
    void setOW(int ow) { this->width = ow; };
    // Sets coordinates and dimensions
    void setOH(int oh) { this->height = oh; };


    // The chess piece is rendered in both boards
    void render();


    /**
    * The chess piece is rendered at a specific location
    * 
    * @param x - The x coordinate that is desired
    * @param y - The y coordinate that is desired
    */
    void render(int x, int y);



    // @return The type of chess piece
    string getType() { return type; };


    //@return The team color of the chess piece
    string getTeam() { return team; };


    // @return The type of moves that the piece can make 
    vector<string> getDirections() { return possibleDirections; };


    /**
    * Checks to see if the chess piece belongs to a certain team
    * 
    * @param team - The team color that is verified
    * @return True if the piece belongs to the same team and false otherwise
    */
    bool sameTeam(string team);
    

    bool isAlive() { return alive; };
    bool isSelected() { return selected; };
    void kill() { this->alive = false; };
};

