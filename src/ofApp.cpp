/*
 
 ofhawc
 
 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetWindowTitle("ofhawc");
    ofBackground(0);
    ofSetColor(255);
    
    // camera
    
    camera.setDistance(100);
    camera.lookAt(nodos[0]);
    //camera.setPosition(0, 0, 0);
    
    // obj
    
    sphere.setRadius(100);
    
    // for para las fuentes
    
    for(int i = 0; i < LIM; i++){
        fuentes[i].setRadius(1.5);
    }
    
    // csv

    buffer = ofBufferFromFile("csv/2HWC_modified.csv"); // reading into the buffer

    
    // bools
    
    spheremode = true;
    domemode = false;
    
    // OSC
    
    sender.setup("127.0.0.1", 5613);
    reciever.setup(5612);
    
    // dome
    
    domemaster.setup();
    domemaster.setCameraPosition(0,0,10);
    
    // fonts
    
    font.load("fonts/DejaVuSansMono.ttf", 10, true, true, true);
    //text = "hola esta es una prueba";
    //portOut = XML.getValue("PORT:NAME:OUT");
    
    // glitch
    
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F_ARB); // 32 es el modo hardcore
    myGlitch.setup(&fbo);
    
    convergence = false;
    glow = false;
    shaker = false;
    cutslider = false;
    twist = false;
    outline = false;
    noise = false;
    slitscan = false;
    swell = false;
    invert = false;
    highcontrast = false;
    blueraise = false;
    redraise = false;
    greenraise = false;
    blueinvert = false;
    redinvert = false;
    greeninvert = false;
    
    // lights
    
    for(int i = 0; i < LIM2; i++){
        clR[i] = 255;
        clG[i] = 255;
        clB[i] = 255;
    }
    
    colorLight1 = ofColor(clR[0], clG[0], clB[0]);
    colorLight2 = ofColor(clR[1], clG[1], clB[1]);
    colorLight3 = ofColor(clR[2], clG[2], clB[2]);
    
    ofSetSmoothLighting(true);
    
    material.setShininess( 50 );
    material.setSpecularColor(ofColor(255, 255, 255, 255));
    
    // radius = 180.f;
    // center.set(ofGetWidth()*.5, ofGetHeight()*.5, 0);
    
    // sources
    
    //  for(int i = 0; i < LIM; i++){
    //    sources[i].loadImage("img/"+ source + ".png");
    //  }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
  camera.orbit(ofGetElapsedTimef()*2, ofGetElapsedTimef()*10, camera.getDistance(), ofVec3f(0, 0, 0));
    
  while (reciever.hasWaitingMessages()){
    ofxOscMessage m;
    reciever.getNextMessage(&m); 
    if (m.getAddress() == "/star" && m.getNumArgs() == 1){
      camera.lookAt(nodos[m.getArgAsInt(0)]);
    }
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofDisableAlphaBlending();
    ofEnableArbTex();
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    // datos //
    
    std::vector < std::string > filas = ofSplitString(buffer.getText(), " ");
    string fuenteNombre = ofToString(filas[1]) + " " + ofToString(filas[2]); // +3 para imprimir los valores de las fuentes. Empieza en 1, 0 es header.

    for (int i = 0;i < 39;i++){
    int paso = (i+1) * 3;
    columna[i] = ofSplitString(filas[paso], ",");
    nodos[i].set(ofToFloat(columna[i][6]), ofToFloat(columna[i][7]), ofToFloat(columna[i][8]) );
    }

    camera.lookAt(nodos[12]);
    string posicionX = " x = " + ofToString(columna[0][6]);
    string posicionY = " y = " + ofToString(columna[0][7]);
    string posicionZ = " z = " + ofToString(columna[0][8]);
    
    // video //
    
    myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE, convergence);
    myGlitch.setFx(OFXPOSTGLITCH_GLOW, glow);
    myGlitch.setFx(OFXPOSTGLITCH_SHAKER, shaker);
    myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER, cutslider);
    myGlitch.setFx(OFXPOSTGLITCH_TWIST, twist);
    myGlitch.setFx(OFXPOSTGLITCH_OUTLINE, outline);
    myGlitch.setFx(OFXPOSTGLITCH_NOISE, noise);
    myGlitch.setFx(OFXPOSTGLITCH_SLITSCAN, slitscan);
    myGlitch.setFx(OFXPOSTGLITCH_SWELL, swell);
    myGlitch.setFx(OFXPOSTGLITCH_INVERT, invert);
    myGlitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, highcontrast);
    myGlitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE, blueraise);
    myGlitch.setFx(OFXPOSTGLITCH_CR_REDRAISE, redraise);
    myGlitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE, greenraise);
    myGlitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT, blueinvert);
    myGlitch.setFx(OFXPOSTGLITCH_CR_REDINVERT, redinvert);
    myGlitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT, greeninvert);
    
    myGlitch.generateFx();

    ofEnableLighting();
    ofEnableDepthTest();
    
    camera.begin();
    
    if(spheremode == true){
        
        sphere.drawWireframe();
        
        ofEnableLighting();
        pointLight.enable();
        //pointLight2.enable();
        //pointLight3.enable();
        material.begin();
        
        //ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        // sphere.drawWireframe();
        
        for (int i = 0;i < 39;i++){
            int paso = 1;
        fuentes[i].setPosition(ofToFloat(columna[i][6]), ofToFloat(columna[i][7]), ofToFloat(columna[i][8]));

        fuentes[i].draw();
        
        }
        
        material.end();
        camera.end();
        
        ofDisableLighting();
        ofDisableDepthTest();

        ofSetColor(255);
        font.drawString(fuenteNombre + posicionX + posicionY + posicionZ, 10, 700);
        
    }
    
    
    if(domemode == true){
        //sphere.drawWireframe();
        for (int i=0; i<domemaster.renderCount; i++){
            domemaster.begin(i);
            drawScene();
            domemaster.end(i);
        }
        
        domemaster.draw();
        
    }
    
    /*
     
     // lo comento en lo que resuelvo los demás problemas
     
     for (int i=0; i<domemaster.renderCount; i++){
     domemaster.begin(i);
     drawScene();
     domemaster.end(i);
     }
     
     domemaster.draw();
     
     */
    
}

//--------------------------------------------------------------
void ofApp::drawScene(){
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofDisableAlphaBlending();
    ofScale(0.125/4, 0.125/4);
    ofTranslate(0, 0, 0);
    ofRotateX(180);
    
    camera.begin();
    sphere.drawWireframe();
    camera.end();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
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
