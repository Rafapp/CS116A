#include "ofApp.h"
#include <glm/gtx/intersect.hpp>

// Global vars
RayTracer rt;

#pragma region openFrameworks
//--------------------------------------------------------------
void ofApp::setup(){
	// General setup
	ofSetBackgroundColor(ofColor::black);

	// Scene
	rt.camera.setPosition(glm::vec3(-20,0,0));
	rt.camera.lookAt(glm::vec3(0,0,0));
	rt.sceneObjects.push_back(new Sphere(glm::vec3(0, 0, .5),1, ofColor::red, ofColor::red));
	rt.sceneObjects.push_back(new Sphere(glm::vec3(-2.5, 0, -0.5), 1, ofColor::green, ofColor::green));
	rt.sceneObjects.push_back(new Sphere(glm::vec3(-5, 0.5, 0), 1, ofColor::blue, ofColor::blue));

	// Raytraced image
	rt.out.allocate(RENDER_WIDTH, RENDER_HEIGHT, OF_IMAGE_COLOR);
	rt.Render();
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){

	rt.camera.begin();

	ofDrawGrid();
	for (SceneObject* object : rt.sceneObjects) {
		object->draw();
	}
	
	rt.camera.end();

	// Drawing our image
	ofSetColor(255);
	rt.out.draw(0,0);
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
	interacting = true;
	cout << interacting << endl;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	interacting = false;
	cout << interacting << endl;
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
void RayTracer::Render(){
	for (int x = 0; x < RENDER_WIDTH; x++) {
		for (int y = 0; y < RENDER_HEIGHT; y++) {
			if(x%2 == 0)
			out.setColor(x, y, ofColor::red);
		}
	}
	rt.out.update();
}

void RayTracer::ProgressiveRender() {}

void RayTracer::Raytrace(){
    
}

bool IntersectLineSphere(Ray ray, Sphere* s) {
	return false;
}
void Ray::draw() {
	ofDrawLine(o, o + (t * d));
}

glm::vec3 Ray::getWorldPoint() {
	return o + (t * d);
}

void Sphere::draw(){
	ofSetColor(diffuseColor);
	ofFill();
	ofDrawSphere(p, r);
}

void Sphere::intersect() {

}
#pragma endregion
