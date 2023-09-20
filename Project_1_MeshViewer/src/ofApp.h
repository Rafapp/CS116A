#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include <iostream>
using namespace std;

/*
 * Mesh class
 */
class Mesh {

    public:

        // Vector of vertices < <x,y,z>>, <x,y,z>, <x,y,z> >
        vector<glm::vec3> verts;

        // Vector of triangles <v1, v2, v3>
        vector<glm::vec3> tris;

        // Size (calculated after setup)
        int triCount = 0;
        int vertCount = 0;

        bool drawAdjacent = false;
        char selectedType = ' ';
        int selectedIndex = 0;

        string path;

        Mesh();
        Mesh(string path);

        void setup();
        void createTestShape();
        void draw();
        void drawSelected(vector<glm::vec3> tris);
        void drawAdjacentTriangles();
};

/*
 * App class
 */

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

        // Variables
        
        
        // Objects
        ofEasyCam cam;
        ofxPanel gui;
        ofxLabel label;
        ofxIntField numberField;
        ofxButton vertexBtn;
        ofxButton triangleBtn;
};

