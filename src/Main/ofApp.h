#pragma once

#include "ofMain.h"
#include "../Game/Board/ChessBoard.h"

class ofApp : public ofBaseApp {


	private:

		ChessBoard* chessBoard;  // The chess board where the game will be played


	public:

		// The first thing the program executes and it only executes one time
		void setup();

		// It is executed on each frame
		// Properties are normally updated here
		void update();

		// It is executed on each frame
		// Rendering normally occurs here
		void draw();


		/**
		* It is executed when a key is pressed
		* 
		* @param key - The key that was pressed
		*/
		void keyPressed(int key);


		/**
		* It is executed when a key is released
		*
		* @param key - The key that was released
		*/
		void keyReleased(int key);


		/**
		* It is executed when the mouse is moved
		*
		* @param x - The x coordinate of the mouse
		* @param y - The y coordinate of the mouse
		*/
		void mouseMoved(int x, int y );


		/**
		* It is executed when the mouse is moving and the button is down
		*
		* @param x - The x coordinate of the mouse
		* @param y - The y coordinate of the mouse
		* @param button - The button that is pressed (left 0, center 1, right 2)
		*/
		void mouseDragged(int x, int y, int button);


		/**
		* It is executed when the button of the mouse is pressed
		*
		* @param x - The x coordinate of the mouse
		* @param y - The y coordinate of the mouse
		* @param button - The button that is pressed (left 0, center 1, right 2)
		*/
		void mousePressed(int x, int y, int button);


		/**
		* It is executed when the button of the mouse is released
		*
		* @param x - The x coordinate of the mouse
		* @param y - The y coordinate of the mouse
		* @param button - The button that is released (left 0, center 1, right 2)
		*/
		void mouseReleased(int x, int y, int button);


		/**
		* It is executed when the mouse cursor enters the window area
		* 
		* @param x - The x coordinate of the mouse from the previous frame
		* @param y - The y coordinate of the mouse from the previous frame
		*/
		void mouseEntered(int x, int y);


		/**
		* It is executed when the mouse cursor leaves the window area
		*
		* @param x - The x coordinate of the mouse from the previous frame
		* @param y - The y coordinate of the mouse from the previous frame
		*/
		void mouseExited(int x, int y);


		/**
		* It is executed when when the application window is resized
		*
		* @param x - The x coordinate of the mouse from the previous frame
		* @param y - The y coordinate of the mouse from the previous frame
		*/
		void windowResized(int w, int h);


		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);


};
