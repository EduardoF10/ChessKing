#pragma once

#include "ofMain.h"

/**
* Implements every aspect of a chess piece
*/
class ChessPiece {

private:

    int ox, oy, ow, oh;  // Overworld Coordinates and dimensions

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
    * @param ox - The x coordinate in pixels of the chess piece
    * @param oy - The y coordinate in pixels of the chess piece
    * @param ow - The width distance in pixels of the chess piece
    * @param oh - The height distance in pixels of the chess piece
    * @param team - The team color of the chess piece
    * @param type - The type of chess piece
    */
    ChessPiece(int ox, int oy, int ow, int oh, string team, string type);


    // The chess piece is rendered in its current location
    void render();


    /**
    * The piece is rendered at ox, oy
    * 
    * @param ox - The x coordinate in pixels
    * @param oy - The y coordinate in pixels
    */
    void render(int ox, int oy);


    // @return The x coordinate in pixels of the chess piece
    int getOX() { return ox; };


    // @return The y coordinate in pixels of the chess piece
    int getOY() { return oy; };


    // @return The width distance in pixels of the chess piece
    int getOW() { return ow; };


    // @return The height distance in pixels of the chess piece
    int getOH() { return oh; };


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
    void setOX(int ox) { this->ox = ox; };
    // Sets coordinates and dimensions
    void setOY(int oy) { this->oy = oy; };
    // Sets coordinates and dimensions
    void setOW(int ow) { this->ow = ow; };
    // Sets coordinates and dimensions
    void setOH(int oh) { this->oh = oh; };



    bool isAlive() { return alive; };
    bool isSelected() { return selected; };
    void kill() { this->alive = false; };
};

