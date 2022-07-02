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
    * @param xL - The x coordinate in pixels of the chess piece in the left board
    * @param yL - The y coordinate in pixels of the chess piece in the left board
    * @param xR - The x coordinate in pixels of the chess piece in the right board
    * @param yR - The y coordinate in pixels of the chess piece in the right board
    * @param w - The width distance in pixels of the chess piece
    * @param h - The height distance in pixels of the chess piece
    * @param team - The team color of the chess piece
    * @param type - The type of chess piece
    */
    ChessPiece(int xL, int yL, int xR, int yR, int w, int h, string team, string type);

    // The chess piece is rendered in the left board
    void renderLeftBoard();

    // The chess piece is rendered in the right board
    void renderRightBoard();


    // The chess piece is rendered in both boards
    void render();


    /**
    * The piece is rendered at ox, oy
    * 
    * @param ox - The x coordinate in pixels
    * @param oy - The y coordinate in pixels
    */
    void render(int ox, int oy);


    // @return The x coordinate in pixels of the chess piece
    int getOX() { return leftX; };


    // @return The y coordinate in pixels of the chess piece
    int getOY() { return leftY; };


    // @return The width distance in pixels of the chess piece
    int getOW() { return width; };


    // @return The height distance in pixels of the chess piece
    int getOH() { return height; };


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


    // Sets coordinates and dimensions
    void setOX(int ox) { this->leftX = ox; };
    // Sets coordinates and dimensions
    void setOY(int oy) { this->rightY = oy; };
    // Sets coordinates and dimensions
    void setOW(int ow) { this->width = ow; };
    // Sets coordinates and dimensions
    void setOH(int oh) { this->height = oh; };



    bool isAlive() { return alive; };
    bool isSelected() { return selected; };
    void kill() { this->alive = false; };
};

