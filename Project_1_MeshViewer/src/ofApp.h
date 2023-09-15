#pragma once

#include "ofMain.h"

#include <iostream>
using namespace std;

/*
 * Mesh class
 */

class Mesh {

public:

	// Vector of vertices < <x,y,z>>, <x,y,z>, <x,y,z> >
	vector<glm::vec3> verts;

	// Vector of triangles <v1, v2, v3>
	vector<glm::vec3> tris;

	// Constructor for testing
	Mesh() {
		createPyramid();
	}

	// Test pyramid
	void createPyramid() {
		verts.push_back(glm::vec3(0, 10, 0));
		verts.push_back(glm::vec3(10, 0, 0));
		verts.push_back(glm::vec3(0, 0, 10));
		verts.push_back(glm::vec3(-10, 0, 0));
		verts.push_back(glm::vec3(0, 0, -10));

		tris.push_back(glm::vec3(1, 0, 2));
		tris.push_back(glm::vec3(2, 0, 3));
		tris.push_back(glm::vec3(3, 0, 4));
		tris.push_back(glm::vec3(4, 0, 1));
		tris.push_back(glm::vec3(1, 4, 2));
		tris.push_back(glm::vec3(2, 4, 3));
	}

	// Draw method
	void draw() {
		for (glm::vec3 tri : tris) {
			ofDrawTriangle(verts[tri[0]], verts[tri[1]], verts[tri[2]]);
		}
	}

};

/*
 * App class
 */

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		// Objects
		ofEasyCam cam;
		Mesh mesh;
};

