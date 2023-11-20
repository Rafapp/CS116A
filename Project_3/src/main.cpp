#include "ofMain.h"
#include "ofApp.h"

//  Project by: Rafael Padilla Perez
//  11/19/2023


//========================================================================
int main( ){
	ofSetupOpenGL(1200,800,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
