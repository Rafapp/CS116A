#pragma once

#include "ofMain.h"

#include <glm/gtx/intersect.hpp>


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
        void drawAxis();
        void calculateRayIntersection(int x, int y);
        
        ofEasyCam easyCam;
        ofCamera sideCam;
        ofCamera topCam;

        ofCamera *theCam;
        
        vector<glm::vec3> testTriangle;
        bool bDrawMouseRay = false;
        glm::vec3 mouseRayOrigin;
        glm::vec3 mouseRayDir;
        glm::vec2 baryV2;
        glm::vec3 baryV3;
        glm::vec3 worldIntersectionCoords;

};
