#pragma once

#include "ofMain.h"

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
		vector<SceneObject> sceneObjects;
};

class SceneObject{
	public:
		glm::vec3 position = glm::vec3(0,0,0);
		ofColor specularColor;
		ofColor diffuseColor;
		virtual void draw();
		virtual void intersect();
};

class Sphere : SceneObject {
	public:
		Sphere() {}
		float r;

};

class Ray {
	public:
		float t;
		glm::vec3 o, d;

		Ray(glm::vec3 o, glm::vec3 d) {
			this->o = o;
			this->d = d;
		}

		glm::vec3 getWorldPoint() { 
			return o + (t * d); 
		}

		void draw() {
			ofDrawLine(o, o + (t * d));
		}
};
