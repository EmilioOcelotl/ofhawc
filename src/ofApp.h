#pragma once

#include "ofMain.h"
#include "ofxDomemaster.h"
#include "ofxPostGlitch.h"
#include "ofxOsc.h"
#include "ofxXmlSettings.h"

#define LIM 39 // fuentes 
#define LIM2 3 

class ofApp : public ofBaseApp{
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
    void drawScene();
    
    ofxDomemaster domemaster;
    ofTrueTypeFont font;
    //ofTrueTypeFont fontobj[LIM];
    string text;
    ofxPostGlitch myGlitch;
    ofFbo fbo;
    ofxOscReceiver reciever;
    ofxOscSender sender;
    ofEasyCam camera;
    ofMaterial material;
    ofxXmlSettings XML;
    ofBuffer buffer;
    ofBuffer curvaDeLuz1;
    ofBuffer curvaDeLuz2;
    ofBuffer curvaDeLuz3;
    string columnas[LIM];
    int pruebaInt;
    string posicionX;
    string posicionY;
    string posicionZ;
    int fuentel;
    int fuenteb;
    ofImage mapa; 

    // string sources[LIM];
    
    // light
    
    ofLight pointLight;
    ofLight pointLight2;
    ofLight pointLight3;
    ofColor colorLight1;
    ofColor colorLight2;
    ofColor colorLight3;
    float radius;
    ofVec3f center;
    
    // color
    
    int clR[LIM2];
    int clG[LIM2];
    int clB[LIM2];
    
    // obj
    
    ofSpherePrimitive sphere;
    ofSpherePrimitive fuentes[LIM];
    float posX[LIM];
    float posY[LIM];
    float posZ[LIM];
    std::vector < std::string > columna[LIM];
    std::vector < std::string > filas;
    ofVec3f nodos[LIM];
    string prueba; 
    
    // bools
    
    bool spheremode;
    bool domemode;
    
    // glitch
    
    bool convergence;
    bool glow;
    bool shaker;
    bool cutslider;
    bool twist;
    bool outline;
    bool noise;
    bool slitscan;
    bool swell;
    bool invert;
    
    bool highcontrast;
    bool blueraise;
    bool redraise;
    bool greenraise;
    bool blueinvert;
    bool redinvert;
    bool greeninvert;
    
};
