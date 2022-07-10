#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

	ofSetFrameRate(60);

	this->mouseCounter = 0;
	this->counterEnabled = false;
	this->dragEnabled = false;

	// Setting up the board
	chessBoard = new ChessBoard("blue");

}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw(){

	// Rendering the status of the board
	chessBoard->render();

	// Renders drag movement if enabled
	if (dragEnabled == true) {
		chessBoard->renderDrag();
	}

	// Enables drag if the mouse was pressed long enough
	else if (counterEnabled == true) {
		mouseCounter += 1;
		if (mouseCounter == 7) {
			dragEnabled = true;
			mouseCounter = 0;
			counterEnabled = false;
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

	// Counter starts
	counterEnabled = true;
	mouseCounter = 0;

	// Processing the tile that was clicked with the left button
	if (button == 0) {
		chessBoard->onClick(x, y);
	}


}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

	// Piece is placed if it was dragged
	if (dragEnabled) {
		chessBoard->placedPiece(x, y);
		chessBoard->resetSelection();
	}

	// Counting ends
	counterEnabled = false;
	dragEnabled = false;

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
