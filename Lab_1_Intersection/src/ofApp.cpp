#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(ofColor::black);
    theCam = &easyCam;

    // camera.screenToWorld(mouse point) -> vec3 point
    // normalize q - p
    // setup cameras
    //
    easyCam.setDistance(20);
    easyCam.setNearClip(.1);

    sideCam.setPosition(glm::vec3(50, 0, 0));
    sideCam.lookAt(glm::vec3(0, 0, 0));
    sideCam.setNearClip(.1);

    topCam.setPosition(glm::vec3(0, 50, 0));
    topCam.lookAt(glm::vec3(0, 0, 0));
    topCam.setNearClip(.1);
    
    testTriangle.push_back(glm::vec3(7,10,3));
    testTriangle.push_back(glm::vec3(5,23,5));
    testTriangle.push_back(glm::vec3(15,10,-5));
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    theCam->begin();
    drawAxis();
    ofNoFill();
    
    // draw Grid
    //
    ofPushMatrix();
    ofSetColor(ofColor::dimGray);
    ofRotateDeg(90);
    ofDrawGridPlane();
    ofPopMatrix();
    
    // Draw mouse ray
    
    if(bDrawMouseRay){
        ofSetColor(ofColor::white);
        ofDrawLine(mouseRayOrigin, mouseRayOrigin + mouseRayDir * 60);
        ofSetColor(ofColor::blue);
        ofDrawSphere(worldIntersectionCoords, .5);
    }
    ofSetColor(ofColor::white);
    ofDrawTriangle(testTriangle[0], testTriangle[1], testTriangle[2]);
    
    // draw the easy cam
    //
    easyCam.draw();

    theCam->end();
}

void ofApp::drawAxis() {
    ofPushMatrix();
    ofTranslate(glm::vec3(0, .02, 0)); // move up slightly
    ofSetColor(ofColor::red);
    ofDrawLine(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0));
    ofSetColor(ofColor::green);
    ofDrawLine(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    ofSetColor(ofColor::blue);
    ofDrawLine(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));
    ofSetColor(ofColor::white);
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
    case OF_KEY_F1:
        theCam = &easyCam;
        break;
    case OF_KEY_F2:
        theCam = &sideCam;
        break;
    case OF_KEY_F3:
        theCam = &topCam;
        break;
    case 'c':
        if(easyCam.getMouseInputEnabled())easyCam.disableMouseInput();
        else easyCam.enableMouseInput();
        break;
    default:
        break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    calculateRayIntersection(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    calculateRayIntersection(x, y);
}

void ofApp::calculateRayIntersection(int x, int y){
    // Mouse ray
    glm::vec3 d = theCam->screenToWorld(glm::vec3(x, y, 0));
    glm::vec3 o = theCam->getPosition();
    glm::vec3 nd = glm::normalize(d - o);
    
    mouseRayOrigin = o;
    mouseRayDir = nd;
    
    float t;
    if(glm::intersectRayTriangle(o, nd, testTriangle[0], testTriangle[1], testTriangle[2], baryV2, t)) bDrawMouseRay = true;
    else bDrawMouseRay = false;
    
    baryV3 = glm::vec3(1.0 - baryV2.x - baryV2.y, baryV2.x, baryV2.y);
    worldIntersectionCoords = baryV3.x * testTriangle[0] + baryV3.y * testTriangle[1] + baryV3.z * testTriangle[2];
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    bDrawMouseRay = false;
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
