#include "ofApp.h"
#include <glm/gtx/intersect.hpp>
#include <Windows.h>

// BY: Rafael Padilla Perez
// 2023

// Global vars
RayTracer rt;
int sampleNumber;
int sampleCount = 10;
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
	gui.add(t_showGrid.setup("Show grid", false));
	gui.add(t_renderPlane.setup("Show last viewplane", false));
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
		rt.bShowImage = true;
		rt.out.setColor(0);
		sampleNumber = sampleCount;
	}
    
    // Save message
    if(b_save) l_save = "Image saved";
    else l_save = "";
}

//--------------------------------------------------------------

void ofApp::draw(){
	ofEnableDepthTest();

	rt.renderCam.begin();
    ofSetColor(ofColor::white);
	
    // Draw objects (OF preview)
	if(t_showGrid) ofDrawGrid();

	for (SceneObject* object : rt.sceneObjects) {
		object->draw();
	}

	if(t_renderPlane) rt.viewPlane.draw();

	rt.renderCam.end();

	ofDisableDepthTest();

	// Display images in viweport
	if (rt.bShowImage) {
		ofSetColor(255);
		rt.out.draw(0, 0); 
		if (sampleNumber > 0) {
			rt.ProgressiveRender();
			sampleNumber--;
		}
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

	rt.viewPlane.update();

	rt.out.allocate(RENDER_WIDTH, RENDER_HEIGHT, OF_IMAGE_COLOR);

	cout << "starting render ..." << endl;
	glm::vec3 o = renderCam.getPosition();
	for (int u = 0; u < RENDER_WIDTH - 1; u++) {
		for (int v = 0; v < RENDER_HEIGHT - 1; v++) {
			out.setColor(u, v, Raytrace(o, u, v));
		}
	}

	rt.out.update();
	rt.bRendered = true;
	cout << "Render complete in:" << ofGetElapsedTimef() - t0 << " s" << endl;
}

// Generates a temporary image via a sampling algorithm
void RayTracer::ProgressiveRender() {
	if (rt.bRendered) return;

	float t0 = ofGetElapsedTimef();

	rt.viewPlane.update();

	rt.out.allocate(RENDER_WIDTH, RENDER_HEIGHT, OF_IMAGE_COLOR);

	cout << "starting render ..." << endl;
	glm::vec3 o = renderCam.getPosition();
	for (int u = 0; u < RENDER_WIDTH - 1; u++) {
		for (int v = 0; v < RENDER_HEIGHT - 1; v++) {
			if (u % sampleNumber == 0 && v % sampleNumber == 0) out.setColor(u, v, Raytrace(o, u, v));
		}
	}
	rt.out.update();

	if(sampleNumber <= 0) rt.bRendered = true;
	cout << "Rendered sample: " << sampleNumber << " in: " << ofGetElapsedTimef() - t0 << " s" << endl;
}

// Traces a ray given at a image -> world coordinate, finds object intersections, returns a pixel color
ofColor RayTracer::Raytrace(glm::vec3 o, int u, int v){
	glm::vec3 d = normalize(rt.viewPlane.PlaneToWorld(u, v) - (o));
	Ray* r = new Ray(o, d);

	float low = FLT_MAX;
	SceneObject* nearest = nullptr;

	for (SceneObject* s : sceneObjects) {
		if (s->intersect(*r, s)) {
			if (s->t < low) {
				low = s->t;
				nearest = s;
			}
		}
	}

	if (nearest) return nearest->diffuseColor;;
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
	rt.viewPlane.n = rt.renderCam.getLookAtDir();
}

// Convert from uv plane coordinates, using 2 basis vectors
glm::vec3 ViewPlane::PlaneToWorld(int u, int v) {
	float nu = (u - RENDER_WIDTH/2.0) / RENDER_WIDTH;
	float nv = (v - RENDER_HEIGHT/2.0) / RENDER_HEIGHT;

	glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), n));
	glm::vec3 down = glm::normalize(glm::cross(right, n)); 

	return rt.viewPlane.p + ((-right * rt.viewPlane.w * nu) + down * rt.viewPlane.h * nv);
}

void Ray::draw() {
	ofSetColor(ofColor::white);
	ofDrawLine(o, o + (t * d));
}

glm::vec3 Ray::getWorldPoint(float t) {
	return o + (t * d);
}

void Sphere::draw(){
	ofSetColor(diffuseColor);
	ofFill();
	ofDrawSphere(p, r);
}

bool Sphere::intersect(Ray ray, SceneObject* s){
	float t;
	Sphere* sphere = dynamic_cast<Sphere*>(s); // TODO: Fix this, it's terrible!
	bool intersect = glm::intersectRaySphere(ray.o, ray.d, s->p, sphere->r * sphere->r, t);
	s->t = t;
	return intersect;
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

bool Plane::intersect(Ray ray, SceneObject* s) {
	float t;
	Plane* plane = dynamic_cast<Plane*>(s); // TODO: Fix this, it's terrible!
	bool intersect = glm::intersectRayPlane(ray.o, ray.d, plane ->p, plane->n, t);
	s->t = t;
	return intersect;
}
#pragma endregion
