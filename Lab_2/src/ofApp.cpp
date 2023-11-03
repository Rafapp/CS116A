#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    verts.push_back(glm::vec3(10, 0, 0));
    verts.push_back(glm::vec3(0, 0, 10));
    verts.push_back(glm::vec3(-10, 0, 0));
    verts.push_back(glm::vec3(0, 0, -10));
    verts.push_back(glm::vec3(0, 10, 0));
    
    gui.setup();
    gui.add(xPos.setup("x", 0.0, -100.0, 100.0));
    gui.add(yPos.setup("y", 0.0, -100.0, 100.0));
    gui.add(zPos.setup("z", 0.0, -100.0, 100.0));
    gui.add(xSpin.setup("rx", 0.0, -100.0, 100.0));
    gui.add(ySpin.setup("ry", 0.0, -100.0, 100.0));
    gui.add(zSpin.setup("rz", 0.0, -100.0, 100.0));
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------

glm::mat4 GetTransform(glm::vec3 p, float rx, float ry, float rz){
    glm::mat4 I(1.0);
    glm::mat4 T = glm::translate(I, p);
    glm::mat4 Rx = glm::rotate(I, glm::radians(rx), glm::vec3(1, 0, 0));
    glm::mat4 Ry = glm::rotate(I, glm::radians(ry), glm::vec3(0, 1, 0));
    glm::mat4 Rz = glm::rotate(I, glm::radians(rz), glm::vec3(0, 0, 1));
    return T * Rx * Ry * Rz;
}

void ofApp::draw(){
    ofSetBackgroundColor(ofColor::black);
    gui.draw();
    cam.begin();
    
    ofPushMatrix();
    ofRotate(90, 0, 0, 1);
    ofSetLineWidth(1);
    ofSetColor(ofColor::dimGrey);
    ofDrawGridPlane();
    ofPopMatrix();
    
    ofSetColor(ofColor::green);
    
    ofPushMatrix();
    glm::mat4 T =  GetTransform(glm::vec3(xPos.getParameter().cast<float>(), yPos.getParameter().cast<float>(), zPos.getParameter().cast<float>()), xSpin, ySpin, zSpin);
    ofMultMatrix(T);
    ofDrawLine(verts[0], verts[1]);
    ofDrawLine(verts[1], verts[2]);
    ofDrawLine(verts[2], verts[3]);
    ofDrawLine(verts[3], verts[0]);
    
    ofDrawLine(verts[0], verts[4]);
    ofDrawLine(verts[1], verts[4]);
    ofDrawLine(verts[2], verts[4]);
    ofDrawLine(verts[3], verts[4]);
    ofPopMatrix();
    
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
