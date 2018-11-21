#pragma once

#include "ofMain.h"
#include "ofxPostGlitch.h"
#include "ofxOsc.h"
#include "ofxXmlSettings.h"
#include "ofxSyphon.h"

#define LIM 39 // fuentes
#define LIMCRAB 4248 // fuentes
#define LIM2 3
#define SOURCENUM 39
#define NUMFILES 3

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
    void miniWin();

    ofTrueTypeFont font;
    //ofTrueTypeFont fontobj[LIM];
    string text;
    ofxPostGlitch myGlitch;
    ofFbo fbo;
    ofxOscReceiver reciever;
    ofxOscSender sender;
    ofEasyCam camera;
    ofMaterial material;
    ofMaterial shMaterial;
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
    int ofmode;
    ofImage mapa;
    int orbitX;
    int orbitY;
    int fuenteObservada;
    int esferaIn;
    int esferaEx;
    
#if (defined(__APPLE__) && defined(__MACH__))
    ofxSyphonClient client;
    bool syphonON;
#endif

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
    int centro;
    
    // color
    
    int clR[LIM2];
    int clG[LIM2];
    int clB[LIM2];
    
    // blur
    
    int blur;
    
    // obj
    
    ofSpherePrimitive sphere;
    ofSpherePrimitive sphere2;
    ofSpherePrimitive sphere3;

    ofSpherePrimitive fuentes[LIM];
    float posX[LIM];
    float posY[LIM];
    float posZ[LIM];
    std::vector < std::string > columna[LIM];
    std::vector < std::string > filas[LIM];
    ofVec3f nodos[LIM];
    string prueba;
    //std::vector < std::string > curva2;
    //std::vector < std::string > curva3;
    string typing;
    string crabo;
    string post; 
    std::vector < std::string > crab;
    
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

    ofBuffer curvaDeLuzBuffer[LIM2];
    float intensidadCrab;
    float intensidadMkr421;
    float intensidadMkr501;
    string fuenteNombre;
    
};
