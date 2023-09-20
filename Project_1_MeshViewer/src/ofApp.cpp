#include "ofApp.h"


Mesh mesh("geo/Woob.obj");

#pragma region Mesh
Mesh::Mesh() { createTestShape(); }

Mesh::Mesh(string path) : path(path) {};

vector<string> split(const string& input, char delimeter) {
    vector<string> values;
    string value;
    stringstream ss(input);

    while (getline(ss, value, delimeter)) {
        values.push_back(value);
    }
    return values;
}

void Mesh::setup() {

    verts.push_back(glm::vec3(0, 0, 0));

    cout << "Loading mesh " << ofToDataPath(path) << "..." << endl;

    ofBuffer buffer = ofBufferFromFile(ofToDataPath(path));

    int vCount = 0;
    int fCount = 0;
    for (string line : buffer.getLines()) {

        if (line.empty()) continue;

        if (line[1] == ' ') {
            vector<float> v; // Verts
            vector<int> f; // Faces
            switch (line[0]) {
            case 'v':
                for (string value : split(line, ' ')) {
                    // ~TODO: Fix this it's super dirty!
                    try {
                        v.push_back(stof(value));
                    }
                    catch (const std::exception e) {}
                }
                verts.push_back(glm::vec3(v[0], v[1], v[2]));
                vCount++;
                cout << "\r" << string(50, ' ') << "\rLoaded vertices : " << vCount << flush;
                break;
            case 'f':
                for (string face : split(line, ' ')) {
                    // ~TODO: Fix this, it's super dirty!
                    try {
                        f.push_back(stoi(split(face, '/')[0]));
                    }
                    catch (const std::exception e) {}
                }
                // Works for any n-gon
//                    for (int i = 0; i < f.size() - 2; i++) {
                tris.push_back(glm::vec3(f[0], f[1], f[2]));
                tris.push_back(glm::vec3(f[0], f[2], f[3]));
                fCount++;
                //                        cout << "\r" << string(50, ' ') << "\rLoaded faces: " << fCount << flush;
                //                    }
                break;
            }
            continue;
        }
    }
    cout << "\r" << string(50, ' ') << "\r";
    cout << "Finished loading model : " << ofToDataPath(path) << endl << flush;
    cout << endl << "---STATS---" << endl;
    cout << "Vertices: " << vCount << endl;
    cout << "Triangles: " << fCount << endl;

    // Vert count * 3 coords (x,y,z) * 4 bytes (float)
    cout << "Vertex memory: " << (vCount * 3 * 4) / 1000. << " kb" << endl;

    // Tri count * 3 indices (v1,v2,v3) * 4 bytes (int)
    cout << "Triangle memory: " << (fCount * 3 * 4) / 1000. << " kb" << endl;

    cout << "Total memory: " << ((vCount * 3 * 4) / 1000. + (fCount * 3 * 4) / 1000.) << " kb" << endl;

    vertCount = vCount;
    triCount = fCount;
}

void Mesh::createTestShape() {
    verts.push_back(glm::vec3(0, 10, 0));
    verts.push_back(glm::vec3(10, 0, 0));
    verts.push_back(glm::vec3(0, 0, 10));
    verts.push_back(glm::vec3(-10, 0, 0));
    verts.push_back(glm::vec3(0, 0, -10));

    tris.push_back(glm::vec3(1, 0, 2));
    tris.push_back(glm::vec3(2, 0, 3));
    tris.push_back(glm::vec3(3, 0, 4));
    tris.push_back(glm::vec3(4, 0, 1));
    tris.push_back(glm::vec3(1, 4, 2));
    tris.push_back(glm::vec3(2, 4, 3));
}

void Mesh::draw() {
    for (glm::vec3 tri : tris) {
        ofDrawTriangle(verts[tri.x], verts[tri.y], verts[tri.z]);
    }
    if (drawAdjacent)
    {
        drawAdjacentTriangles();
    }
}
void Mesh::drawSelected(vector<glm::vec3> tris) {
    ofSetColor(ofColor::green);
    ofFill();
    for (glm::vec3 tri : tris) {
        ofDrawTriangle(verts[tri.x], verts[tri.y], verts[tri.z]);
    }

    ofSetColor(ofColor::white);
    ofNoFill();
    for (glm::vec3 tri : tris) {
        ofDrawTriangle(verts[tri.x], verts[tri.y], verts[tri.z]);
    }
}

void Mesh::drawAdjacentTriangles() {
    // Select adjacent tris to face
    if (selectedType == 'f') {

        if (selectedIndex > triCount) return;

        vector<glm::vec3> temp;
        glm::vec3 triIndexes = tris[selectedIndex];
        for (glm::vec3 tri : tris) {
            int contained = 0;
            for (int i = 0; i < 3; i++) {
                if (triIndexes.x == tri[i] || triIndexes.y == tri[i] || triIndexes.z == tri[i]) contained++;
                if (contained >= 2) {
                    temp.push_back(tri);
                    cout << "BREAK: " << contained << endl;
                    break;
                }
            }
            //            if ((tri.x == triIndexes.x && tri.y == triIndexes.y) || (tri.y == triIndexes.y && tri.z == triIndexes.z) || (tri.z == triIndexes.z && tri.x == triIndexes.x)) {
            //                temp.push_back(tri);
            //            }
        }
        mesh.drawSelected(temp);
    }

    // Select adjacent tris to vertex
    else if (selectedType == 'v') {
        if (selectedIndex > vertCount) return;

        vector<glm::vec3> temp;
        for (glm::vec3 tri : tris) {
            if (tri.x == selectedIndex || tri.y == selectedIndex || tri.z == selectedIndex) {
                temp.push_back(tri);
            }
        }
        mesh.drawSelected(temp);
    }
}


#pragma endregion

#pragma region OF
//--------------------------------------------------------------
void ofApp::setup() {
    // Camera
    ofSetBackgroundColor(ofColor::black);
    cam.setDistance(10);
    cam.setNearClip(.1);

    // Mesh
    mesh.setup();

    // GUI
    gui.setup();
    gui.add(numberField.setup("Vertex/face #", 0, 1, INT_MAX));
    gui.add(label.setup("", "Select nearby triangles"));
    gui.add(vertexBtn.setup("Index is vertex"));
    gui.add(triangleBtn.setup("Index is triangle"));
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
    cam.begin();

    // Grid
    ofPushMatrix();
    ofSetColor(ofColor::dimGray);
    ofRotateDeg(90);
    ofDrawGridPlane();
    ofPopMatrix();

    // Draw mesh
    ofSetColor(ofColor::white);
    ofNoFill();
    mesh.draw();

    cam.end();

    // GUI
    gui.draw();
    if (vertexBtn) {
        mesh.selectedType = 'v';
        mesh.selectedIndex = numberField;
        mesh.drawAdjacent = true;
    }
    else if (triangleBtn) {
        mesh.selectedType = 'f';
        mesh.selectedIndex = numberField;
        mesh.drawAdjacent = true;
    }
    else
    {
        mesh.selectedType = ' ';
        mesh.drawAdjacent = false;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
#pragma endregion
