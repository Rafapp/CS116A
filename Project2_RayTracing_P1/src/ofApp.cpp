#include "ofApp.h"
#include <glm/gtx/intersect.hpp>
#include <glm/gtc/epsilon.hpp>

// Global vars
RayTracer rt;

#pragma region Helper Functions
// Checks if 2 matrices of any size are identical, component wise.
template<typename T>
bool IsIdentical(const T& mat1, const T& mat2, float epsilon){
    //cout << "COMPARING " << endl << mat1 << endl << " AND " << endl << mat2 << endl;
    int rows = mat1.length();
    int cols = mat2.length();
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(glm::abs(mat1[i][j] - mat2[i][j]) > epsilon) return false;
        }
    }
    return true;
}
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
    gui.add(b_setCamera.setup("Set render to viewport"));
    gui.add(b_raytrace.setup("Raytrace image"));
    gui.add(b_save.setup("Save image ..."));
    gui.add(l_save.setup("", ""));

	// Scene objects
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
glm::vec3 prevView;
void ofApp::update(){
    glm::vec3 view = previewCam.getPosition();
    cout << endl << view << endl;
    
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
    
	// Drawing rendered image
	//ofSetColor(255);
	//rt.out.draw(0,0);
    
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
