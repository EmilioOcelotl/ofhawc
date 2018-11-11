/*
 
 ofhawc
 
 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetWindowTitle("ofhawc");
    ofBackground(0);
    ofSetColor(255);
    ofSetFrameRate(30);

    // camera
    
    camera.setDistance(100);
    
    prueba = "2HWC J0534+220 l=184.546552486 b=-5.78316902994 RA=83.6279 Dec=22.0243";
    pruebaInt = 0;
    //camera.setPosition(0, 0, 0);
    
    // obj
    
    sphere.setRadius(200);
    //sphere.setResolution(20);
    mapa.load("maps/1.png");

    // for para las fuentes
    
    for(int i = 0; i < LIM; i++){
        fuentes[i].setRadius(2);
    }
    
    // csv

    buffer = ofBufferFromFile("csv/2HWC_modified-2.csv"); // reading into the buffer
    curvaDeLuz1 =  ofBufferFromFile("dat/HAWC_fluxlc_Crab_2014-11-26_2016-06-02_1days_si2.63_co1000000_int1.00TeV_mintransits0.50.dat");
    curvaDeLuz2 =  ofBufferFromFile("dat/HAWC_fluxlc_Mrk421_2014-11-26_2016-06-02_1days_si2.2_co5_int2.00TeV_mintransits0.50.dat");
    curvaDeLuz3 =  ofBufferFromFile("dat/HAWC_fluxlc_Mrk501_2014-11-26_2016-06-02_1days_si1.6_co6_int3.00TeV_mintransits0.50.dat");

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
    
    font.load("fonts/DejaVuSansMono.ttf", 16, true, true, true);
    //text = "hola esta es una prueba";
    //portOut = XML.getValue("PORT:NAME:OUT");
    
    // glitch
    
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA12, 8); // 32 es el modo hardcore
    
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
    
    material.setShininess( 120 );
    material.setSpecularColor(ofColor(255, 255, 255, 255));
    
    // datos //
    
    // posiciones
    
    std::vector < std::string > filas = ofSplitString(buffer.getText(), " ");
    //string fuenteNombre = ofToString(filas[1]) + " " + ofToString(filas[2]); // +3 para imprimir los valores de las fuentes. Empieza en 1, 0 es header.
    for (int i = 0;i < 39;i++){
        int paso = (i+1) * 3;
        columna[i] = ofSplitString(filas[paso], ",");
        nodos[i].set(ofToFloat(columna[i][6]), ofToFloat(columna[i][7]), ofToFloat(columna[i][8]) );
    }
    
    // curvas de luz
    
    std::vector < std::string > curva1 = ofSplitString(curvaDeLuz1.getText(), "    ");
    std::vector < std::string > curva2 = ofSplitString(curvaDeLuz2.getText(), "    ");
    std::vector < std::string > curva3 = ofSplitString(curvaDeLuz3.getText(), "    ");

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
      //camera.lookAt(nodos[m.getArgAsInt(0)]);
        prueba = m.getArgAsString(0);
        int paso2 = m.getArgAsInt(0) * 3;
        string fuenteNombre = ofToString(filas[paso2+1]) + " " + ofToString(filas[paso2+2]); // +3 para imprimir los valores de las fuentes. Empieza en 1, 0 es header.
        posicionX = fuenteNombre + " l=" + ofToString(columna[ofToInt(prueba)][1]);
        posicionY = " b=" + ofToString(columna[ofToInt(prueba)][2]) + " RA=" + ofToString(columna[ofToInt(prueba)][3]) + " Dec=" + ofToString(columna[ofToInt(prueba)][4]);
        mapa.load("maps/"+ofToString(m.getArgAsInt(0)+1)+".png");
        //posicionZ = " z = " + ofToString(columna[ofToInt(prueba)][8]);
    }
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofEnableAlphaBlending();
    ofEnableArbTex();
    ofSetRectMode(OF_RECTMODE_CORNER);
    
    //camera.setPosition(0, 0, 0);
    
    // video //
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    ofEnableLighting();
    //ofEnableArbTex();
    //fDisableAlphaBlending();
    ofEnableDepthTest();
    ofTranslate(0, 0, 0);
    camera.lookAt(nodos[ofToInt(prueba)]);
    
    drawScene();
    
}

//--------------------------------------------------------------
void ofApp::drawScene(){
    

    camera.begin();
    ofSetColor(102, 255, 102);
    
    sphere.drawWireframe();
    
    ofEnableLighting();
    pointLight.enable();
    //pointLight2.enable();
    //pointLight3.enable();
    material.begin();
    
    for (int i = 0;i < 39;i++){
        int paso = 1;
        fuentes[i].setPosition(ofToFloat(columna[i][6]), ofToFloat(columna[i][7]), ofToFloat(columna[i][8]));
        ofSetColor(255,255, 255);
        fuentes[i].draw();
    }
    
    material.end();
    camera.end();
    
    ofDisableLighting();
    ofDisableDepthTest();
    
    ofSetColor(102, 255, 102);
    font.drawString( "Nombre="+posicionX + posicionY + posicionZ + prueba, 20, 30);
    font.drawString( "Seleccionar fuente", 20, 60);

    ofNoFill();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    glLineWidth(0.1);
    ofDrawLine(-ofGetWidth()/64, 0, ofGetWidth()/64,0);
    ofDrawLine(0, -ofGetWidth()/64, 0, ofGetWidth()/64);
    ofSetColor(200, 200, 200);
    mapa.draw(ofGetWidth()/2-125, ofGetHeight()/2-110, 300, 225);
    ofSetColor(102, 255, 102);
    font.drawString("Curvas de Luz", -ofGetWidth()/2+20, ofGetHeight()/4-40);

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
