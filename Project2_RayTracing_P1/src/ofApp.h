#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#define RENDER_WIDTH 1280
#define RENDER_HEIGHT 720

#pragma region Raytracing
class Ray {
public:
	Ray(glm::vec3 o, glm::vec3 d) : o(o), d(d), t(0.0) {}
	void draw();
	glm::vec3 getWorldPoint(float t);

	float t;
	glm::vec3 o, d;
};

class SceneObject {
public:

	// TODO: Add a t parameter here, so that we can set it
	// on each raytrace, sort by distance, and then render the pixel

	SceneObject(glm::vec3 p, ofColor diffuseColor, ofColor specularColor)
		: p(p), diffuseColor(diffuseColor), specularColor(specularColor) {};
	virtual void draw() = 0;
	virtual bool intersect(Ray r) = 0;

	glm::vec3 p = glm::vec3(0, 0, 0);
	ofColor diffuseColor, specularColor;
};

class Sphere : public SceneObject {
public:
	Sphere(glm::vec3 p, float r, ofColor diffuseColor, ofColor specularColor)
		: SceneObject(p, diffuseColor, specularColor), r(r) {
	}
	void draw();
	bool intersect(Ray r, Sphere* s);
	float r;
};

class Plane : public SceneObject {
public:
	Plane(glm::vec3 p, glm::vec3 n, float w, float h, ofColor diffuseColor, ofColor specularColor)
		: SceneObject(p, diffuseColor, specularColor), n(n), w(w), h(h)  {
	}
	void draw();
	bool intersect(Ray r);

	ofPlanePrimitive plane;
	glm::vec3 n;
	float w;
	float h;
};

class ViewPlane : ofBaseApp{
public:
	void draw();
	void update(); // Update the view plane to make it match the render camera's
	glm::vec3 PlaneToWorld(int u, int v);

	ofPlanePrimitive plane;
	glm::vec3 p = glm::vec3(0,0,0);

	float w = RENDER_WIDTH / 100.;
	float h = RENDER_HEIGHT / 100.;
};

class RayTracer : ofBaseApp {
public:
	ofEasyCam renderCam;

	ViewPlane viewPlane;
	ofImage out;

	vector<SceneObject*> sceneObjects;

	bool bShowImage;
	bool bRendered;
    
	virtual void Render();
	virtual ofColor Raytrace(glm::vec3 o, int x, int y);
	virtual void ProgressiveRender();
};
#pragma endregion

#pragma region OF
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

		bool bInteracting = false;
		bool bMouseButton = false;
    
        ofxPanel gui;
        ofxLabel l_title;

		ofxLabel l_rendering;
        ofxToggle t_pRendering;
		ofxButton b_render;

		ofxLabel l_controls;
		ofxToggle t_renderPlane;
        ofxButton b_setCamera;

        ofxButton b_save;
		ofxLabel l_save;
};
#pragma endregion


