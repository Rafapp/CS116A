#include "ofApp.h"

Mesh mesh("geo\\cube.obj");

#pragma region Mesh
Mesh::Mesh() { createTestShape(); }

Mesh::Mesh(string path) : path(path) {};

vector<string> split(const string& input, char delimeter) {
	vector<string> values;
	string value;
	stringstream ss(input);

	while (getline(ss, value, delimeter)) {
		values.push_back(value);
	}
	return values;
}

void Mesh::setup() {

	verts.push_back(glm::vec3(0, 0, 0));

	cout << "Opening: " << ofToDataPath(path) << " ..." << endl;
	ofBuffer buffer = ofBufferFromFile(ofToDataPath(path));

	for (string line : buffer.getLines()) {

		if (line.empty()) continue;

		if (line[1] == ' ') {
			vector<float> v; // Verts
			vector<int> f; // Faces
			switch (line[0]) {
				case 'v':
					for (string value : split(line, ' ')) {
						// ~TODO: Fix this it's super dirty!
						try {
							v.push_back(stof(value));
						}
						catch (const std::exception e) {} 
					}
					verts.push_back(glm::vec3(v[0], v[1], v[2]));
					break;
				case 'f':
					for (string face : split(line, ' ')) {
						// ~TODO: Fix this, it's super dirty!
						try {
							f.push_back(stoi(split(face, '/')[0]));
						}
						catch (const std::exception e) {}
					}
					// Works for any n-gon
					for (int i = 0; i < f.size() - 2; i++) {
						tris.push_back(glm::vec3(f[i], f[i + 1], f[i + 2]));
					}
					break;
				}
			continue;
		}
	}
}

void Mesh::createTestShape() {
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

void Mesh::draw() {
	for (glm::vec3 tri : tris) {
		ofDrawTriangle(verts[tri.x], verts[tri.y], verts[tri.z]);
	}
}


#pragma endregion

#pragma region OF
//--------------------------------------------------------------
void ofApp::setup(){
	// Camera
	ofSetBackgroundColor(ofColor::black);
	cam.setDistance(10);
	cam.setNearClip(.1);
	ofEnableDepthTest();

	// Mesh
	mesh.setup();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();

	// Grid
	ofPushMatrix();
	ofSetColor(ofColor::dimGray);
	ofRotateDeg(90);
	ofDrawGridPlane();
	ofPopMatrix();

	// Draw mesh
	ofSetColor(ofColor::white);
	ofNoFill();
	mesh.draw();

	cam.end();
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
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
#pragma endregion
