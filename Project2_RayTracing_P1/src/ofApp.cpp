#include "ofApp.h"
#include <glm/gtx/intersect.hpp>
#include <glm/gtc/epsilon.hpp>

// Global vars
RayTracer rt;

#pragma region Helper Functions
#pragma endregion

#pragma region openFrameworks
//--------------------------------------------------------------
void ofApp::setup(){
	// General setup
	ofSetBackgroundColor(ofColor::black);
    
    // GUI
    gui.setup();
    gui.add(l_title.setup("", "RAYTRACER:By@Rafagamedev"));
    gui.add(t_pRendering.setup("Progressive rendering", false));
    gui.add(b_setCamera.setup("Set render cam to view"));
    gui.add(b_render.setup("Render image"));
    gui.add(b_save.setup("Save image ..."));
    gui.add(l_save.setup("", ""));

	// Scene objects
	previewCam.setPosition(glm::vec3(-20,0,0));
	previewCam.lookAt(glm::vec3(0,0,0));
    
	rt.sceneObjects.push_back(new Sphere(glm::vec3(0, 0, .5),1, ofColor::red, ofColor::red));
	rt.sceneObjects.push_back(new Sphere(glm::vec3(-2.5, 0, -0.5), 1, ofColor::green, ofColor::green));
	rt.sceneObjects.push_back(new Sphere(glm::vec3(-5, 0.5, 0), 1, ofColor::blue, ofColor::blue));

	// Raytraced image
	
}

//--------------------------------------------------------------
glm::vec3 prevPos;
void ofApp::update(){

	// Check if interacting with camera
    glm::vec3 pos = previewCam.getPosition();
    if(prevPos != pos){
		rt.bShowImage = false;
        bInteracting = true;
        prevPos = pos;
    } else bInteracting = false;

	// Render and display image
	if (b_render && !rt.bShowImage) {
		rt.bRendered = false;
		rt.Render();
		rt.bShowImage = true;
	} 

	// Progressively render, and display image
	if (t_pRendering && !bInteracting && bMouseButton == false && !rt.bShowImage) {
		rt.bRendered = false;
		rt.ProgressiveRender();
		rt.bShowImage = true;
	}
    
    // Save message
    if(b_save) l_save = "Image saved";
    else l_save = "";
}

//--------------------------------------------------------------
void ofApp::draw(){

	previewCam.begin();
    ofSetColor(ofColor::white);

    // Draw objects (OF preview)
	ofDrawGrid();
	for (SceneObject* object : rt.sceneObjects) {
		object->draw();
	}
	previewCam.end();

	// Display images in viweport
	if (rt.bShowImage) {
		ofSetColor(255);
		rt.out.draw(0, 0); 
	}
	
    
    // Draw GUI
    gui.draw();
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
	bMouseButton = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	bMouseButton = false;
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
// Generates the final image pixel by pixel
void RayTracer::Render(){
	if (rt.bRendered) return;
	rt.out.allocate(RENDER_WIDTH, RENDER_HEIGHT, OF_IMAGE_COLOR);

	for (int x = 0; x < RENDER_WIDTH; x++) {
		for (int y = 0; y < RENDER_HEIGHT; y++) {
			out.setColor(x, y, ofColor::red);
		}
	}

	rt.out.update();
	rt.bRendered = true;
}

// Generates a temporary image via a sampling algorithm
void RayTracer::ProgressiveRender() {

}

// Traces a ray given at a screen -> world coordinate, finds object intersections, returns a color
ofColor RayTracer::Raytrace(glm::vec3 o, int x, int y){
	//glm::vec3 d = rt.renderCam.cameraToWorld(x, y);
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
