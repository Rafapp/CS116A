#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#define RENDER_WIDTH 1280.0
#define RENDER_HEIGHT 720.0

//BY: Rafael Padilla Perez
//2023
#pragma region Raytracing
class Ray {
public:
    Ray(glm::vec3 o, glm::vec3 d) : o(o), d(d), t(20) {}
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
    virtual bool intersect(Ray r, SceneObject* s) = 0;

    float t = FLT_MAX; // The distance to the intersection
    glm::vec3 p = glm::vec3(0, 0, 0);
    ofColor diffuseColor, specularColor;
};

class Sphere : public SceneObject {
public:
    Sphere(glm::vec3 p, float r, ofColor diffuseColor, ofColor specularColor)
        : SceneObject(p, diffuseColor, specularColor), r(r) {
    }
    void draw();
    bool intersect(Ray r, SceneObject* s);
    float r;
};

class Plane : public SceneObject {
public:
    Plane(glm::vec3 p, glm::vec3 n, float w, float h, ofColor diffuseColor, ofColor specularColor)
        : SceneObject(p, diffuseColor, specularColor), n(n), w(w), h(h) {
    }
    void draw();
    bool intersect(Ray r, SceneObject* s);

    ofPlanePrimitive plane;
    glm::vec3 n;
    float w;
    float h;
};

class ViewPlane : ofBaseApp {
public:
    void draw();
    void update(); // Update the view plane to make it match the render camera's
    glm::vec3 PlaneToWorld(int u, int v);

    ofPlanePrimitive plane;
    glm::vec3 n;
    glm::vec3 p = glm::vec3(0, 0, 0);

    float w = RENDER_WIDTH / 100.;
    float h = RENDER_HEIGHT / 100.;
};

class Light {
public:
    glm::vec3 p;
    float i;

    virtual void draw() = 0;
    virtual int getRaySamples(glm::vec3 hitPoint, vector<Ray*> &samples) = 0;

    Light(glm::vec3 p, float i) : p(p), i(i) {}
};

class PointLight : public Light {
public:
    void draw() {
        ofSetColor(ofColor::yellow);
        ofDrawSphere(p, .2);
    };

    virtual int getRaySamples(glm::vec3 hitPoint, vector<Ray*>& samples);

    PointLight(glm::vec3 p, float i) : Light(p, i) {}
};

class AreaLight : public Light {
public:
    float width = 5, height = 5;
    int nDivsWidth = 10, nDivsHeight = 10;
    int nSamples = 1;
    ofPlanePrimitive plane;

    void draw() {
        ofFill();
        ofSetColor(ofColor::yellow);
        plane.setPosition(p);
        plane.setWidth(width);
        plane.setHeight(height);
        plane.setResolution(2, 2);
        plane.setOrientation(glm::vec3(90,0,0));
        plane.draw();
    };

    virtual int getRaySamples(glm::vec3 hitPoint, vector<Ray*>& samples);

    AreaLight(glm::vec3 p, float i) : Light(p, i) {}
};

class RayTracer : ofBaseApp {
public:
    ofEasyCam renderCam;

    ViewPlane viewPlane;
    ofImage out;

    vector<SceneObject*> sceneObjects;
    vector<Light*> lights;

    bool bShowImage;
    bool bRendered;

    virtual void Render();
    virtual SceneObject* Raytrace(glm::vec3 o, int x, int y, Ray& rOut);
    virtual void ProgressiveRender();
    ofColor lambert(const ofColor& diffuse, float intensity, float distance, const glm::vec3& n, const glm::vec3& l);
    ofColor phong(const ofColor& specular, float intensity, float distance, float pow, const glm::vec3& n, const glm::vec3& l, const glm::vec3& v);
};
#pragma endregion

#pragma region OF


class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
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

    /*
     * GUI
     */

    ofxPanel gui;
    ofxLabel l_title;

    // Render settings
    ofxLabel l_rendering;
    ofxToggle t_pRendering;
    ofxButton b_render;

    // Preview controls
    ofxLabel l_controls;
    ofxToggle t_showGrid;
    ofxToggle t_renderPlane;

    // Shading controls
    ofxLabel l_shading;

    // Area light controls
    ofxLabel l_lights;

    ofxGuiGroup g_dimensions;
    ofxFloatField f_areaLightWidth;
    ofxFloatField f_areaLightHeight;

    ofxGuiGroup g_position;
    ofxFloatField f_areaLightx;
    ofxFloatField f_areaLighty;
    ofxFloatField f_areaLightz;

    ofxGuiGroup g_sampling;
    ofxIntField i_nDivsWidth;
    ofxIntField i_nDivsHeight;
    ofxIntField i_nSamples;

    ofxButton b_save;
    ofxLabel l_save;
};
#pragma endregion
