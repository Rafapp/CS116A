#pragma once

#include "ofMain.h"

#pragma region Raytracing
class SceneObject {
public:
	SceneObject(glm::vec3 p, ofColor diffuseColor, ofColor specularColor)
		: p(p), diffuseColor(diffuseColor), specularColor(specularColor) {};

	glm::vec3 p = glm::vec3(0, 0, 0);
	ofColor diffuseColor, specularColor;
	virtual void draw() = 0;
	virtual void intersect() = 0;
};

class Sphere : public SceneObject {
public:
	Sphere(glm::vec3 p, float r, ofColor diffuseColor, ofColor specularColor)
		: SceneObject(p, diffuseColor, specularColor), r(r) {
	}
	void draw();
	void intersect();
	float r;
};

class Ray {
public:
	float t;
	glm::vec3 o, d;
	Ray(glm::vec3 o, glm::vec3 d) : o(o), d(d), t(0.0) {}
	glm::vec3 getWorldPoint();
	void draw();

};
#pragma endregion

#pragma region OF
class ofApp : public ofBaseApp{
	public:
		#pragma region OF
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
		#pragma endregion
		ofEasyCam camera;
		vector<SceneObject*> sceneObjects;
};
#pragma endregion
