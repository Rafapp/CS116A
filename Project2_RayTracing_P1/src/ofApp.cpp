#include "ofApp.h"
#include <glm/gtx/intersect.hpp>

// Global vars
RayTracer rt;
// To save: img.save("myPic.jpg");

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

	gui.add(l_rendering.setup("", "Rendering"));
    gui.add(t_pRendering.setup("Progressive rendering", false));
	gui.add(b_render.setup("Render image"));

	gui.add(l_controls.setup("", "Controls"));
    gui.add(b_setCamera.setup("Align render to view"));
	gui.add(t_renderPlane.setup("Show render plane", false));
    gui.add(b_save.setup("Save image ..."));
    gui.add(l_save.setup("", ""));

	// Preview cam
	rt.renderCam.setPosition(glm::vec3(-20,0,0));
	rt.renderCam.lookAt(glm::vec3(0,0,0));
    
	// Scene objects
	rt.sceneObjects.push_back(new Plane(glm::vec3(0, -5, 0), glm::vec3(0, 1, 0), 20, 20, ofColor::lightGray, ofColor::lightGray));

	rt.sceneObjects.push_back(new Sphere(glm::vec3(0, 0, .5),1, ofColor::red, ofColor::red));
	rt.sceneObjects.push_back(new Sphere(glm::vec3(-2.5, 0, -0.5), 1, ofColor::green, ofColor::green));
	rt.sceneObjects.push_back(new Sphere(glm::vec3(-5, 0.5, 0), 1, ofColor::blue, ofColor::blue));
	
}

//--------------------------------------------------------------
glm::vec3 prevPos;
void ofApp::update(){

	// Check if interacting with camera
    glm::vec3 pos = rt.renderCam.getPosition();
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

	// Update the view plane position to the frustum's near plane
	if (b_setCamera) {
		rt.viewPlane.update();
	}
    
    // Save message
    if(b_save) l_save = "Image saved";
    else l_save = "";
}

//--------------------------------------------------------------
void ofApp::draw(){

	rt.renderCam.begin();
    ofSetColor(ofColor::white);
	
    // Draw objects (OF preview)
	ofDrawGrid();
	for (SceneObject* object : rt.sceneObjects) {
		object->draw();
	}

	if(t_renderPlane) rt.viewPlane.draw();

	rt.renderCam.end();

	// Display images in viweport
	if (rt.bShowImage) {
		ofSetColor(255);
		rt.out.draw(0, 0); 
	}

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
	float t0 = ofGetElapsedTimef();
	rt.out.allocate(RENDER_WIDTH, RENDER_HEIGHT, OF_IMAGE_COLOR);

	for (int x = 0; x < RENDER_WIDTH; x++) {
		for (int y = 0; y < RENDER_HEIGHT; y++) {
			out.setColor(x, y, ofColor::red);
		}
	}

	rt.out.update();
	rt.bRendered = true;
	cout << "Render complete in:" << ofGetElapsedTimef() - t0 << " s" << endl;
}

// Generates a temporary image via a sampling algorithm
void RayTracer::ProgressiveRender() {

}

// Traces a ray given at a screen -> world coordinate, finds object intersections, returns a color
ofColor RayTracer::Raytrace(glm::vec3 o, int u, int v){
	glm::vec3 d = rt.viewPlane.PlaneToWorld(u, v);
	return ofColor::black;
}

// Draw the view plane for debugging
void ViewPlane::draw() {
	ofNoFill();
	ofSetColor(ofColor::green);
	plane.setPosition(p);
	plane.setWidth(w);
	plane.setHeight(h);
	plane.setResolution(2, 2);
	plane.drawWireframe();
}

// Position and align view plane with camera frustum's near plane
void ViewPlane::update(){
	rt.viewPlane.p = rt.renderCam.getPosition() + rt.renderCam.getLookAtDir() * rt.renderCam.getNearClip();
	rt.viewPlane.plane.setOrientation(rt.renderCam.getOrientationQuat());
}

// Convert from uv plane coordinates, to world
glm::vec3 ViewPlane::PlaneToWorld(int u, int v) {
	return glm::vec3(0);
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

bool Sphere::intersect(Ray r) {
	return false;
}

void Plane::draw() {
	ofSetColor(diffuseColor);
	ofFill();
	plane.setPosition(p);
	plane.setWidth(w);
	plane.setHeight(h);
	plane.setResolution(4, 4);

	ofQuaternion rot;
	rot.makeRotate(glm::vec3(0, 0, -1), n);
	plane.setOrientation(rot);

	plane.draw();
}

bool Plane::intersect(Ray r) {
	return false;
}
#pragma endregion
