#include "ofApp.h"
#include <glm/gtx/intersect.hpp>

#pragma region openFrameworks
//--------------------------------------------------------------
void ofApp::setup(){
	ofEnableDepthTest();
	ofSetBackgroundColor(ofColor::black);

	camera.setPosition(glm::vec3(-20,0,0));
	camera.lookAt(glm::vec3(0,0,0));
	sceneObjects.push_back(new Sphere(glm::vec3(0, 0, .5),1, ofColor::red, ofColor::red));
	sceneObjects.push_back(new Sphere(glm::vec3(-2.5, 0, -0.5), 1, ofColor::green, ofColor::green));
	sceneObjects.push_back(new Sphere(glm::vec3(-5, 0.5, 0), 1, ofColor::blue, ofColor::blue));
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	camera.begin();

	ofDrawGrid();
	for (SceneObject* object : sceneObjects) {
		object->draw();
	}
	camera.end();
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

#pragma region RayTracing
void Ray::draw() {
	ofDrawLine(o, o + (t * d));
}

glm::vec3 Ray::getWorldPoint() {
	return o + (t * d);
}

void Sphere::draw(){
	cout << "DRAWING SPHERE" << endl;
	ofSetColor(diffuseColor);
	ofFill();
	ofDrawSphere(p, r);
}

void Sphere::intersect() {

}
#pragma endregion