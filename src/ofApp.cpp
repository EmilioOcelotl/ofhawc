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
    //prueba = "0";
    pruebaInt = 0;
    //camera.setPosition(0, 0, 0);
    
    // obj
    
    sphere.setRadius(200);
    sphere.setResolution(30);
    sphere2.setRadius(100);
    sphere2.setResolution(15);
    mapa.load("maps/1.png");
    typing = "ENTER para escribir o ENTER + h + ENTER para ayuda";
    intensidad = 0.06;

    // for para las fuentes
    
    for(int i = 0; i < LIM; i++){
        fuentes[i].setRadius(2);
    }
    
    // csv

    buffer = ofBufferFromFile("csv/2HWC_modified-2.csv"); // reading into the buffer
    
    // bools
    
    spheremode = true;
    domemode = false;
    
    // OSC
    
    sender.setup("192.168.1.67", 57120);
    reciever.setup(5612);
    
    // fonts
    
    font.load("fonts/DejaVuSansMono.ttf", 12, true, true, true);
    //text = "hola esta es una prueba";
    //portOut = XML.getValue("PORT:NAME:OUT");
    
    // glitch
    
    //fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA, 8);
    
    // lights
    
    for(int i = 0; i < LIM2; i++){
        clR[i] = 255*0.5;
        clG[i] = 255*0.5;
        clB[i] = 255*0.5;
    }
    
    //colorLight1 = ofColor(clR[0], clG[0], clB[0]);
    //colorLight2 = ofColor(clR[1], clG[1], clB[1]);
    //colorLight3 = ofColor(clR[2], clG[2], clB[2]);
    
    
    
    colorLight1 = ofColor(255.f, 113.f, 206.f);
    colorLight2 = ofColor( 1.f, 205.f, 254.f );
    colorLight3 = ofColor(185.f, 103.f, 255.f);
    
     pointLight.setDiffuseColor( colorLight1 );
    pointLight.setSpecularColor( colorLight1 );
    pointLight2.setDiffuseColor( colorLight2 );
    pointLight2.setSpecularColor( colorLight2 );
    pointLight3.setDiffuseColor( colorLight3 );
    pointLight3.setSpecularColor( colorLight3 );
    
    ofSetSmoothLighting(true);
    
    material.setShininess( 20 );
    material.setSpecularColor(ofColor(255, 255, 255, 255));
    
    // datos //
    
    // posiciones
    
    std::vector < std::string > filas = ofSplitString(buffer.getText(), " ");
    string fuenteNombre = ofToString(filas[1]) + " " + ofToString(filas[2]); // +3 para imprimir los valores de las fuentes. Empieza en 1, 0 es header.
    for (int i = 0;i < 39;i++){
        int paso = (i+1) * 3;
        columna[i] = ofSplitString(filas[paso], ",");
        nodos[i].set(ofToFloat(columna[i][6]), ofToFloat(columna[i][7]), ofToFloat(columna[i][8]) );
    }
    
    //crabo = " " + curvasDeLuz[1][2] + curvasDeLuz[2][5] + curvasDeLuz[1][8];

}

//--------------------------------------------------------------
void ofApp::update(){
    
    pointLight.setPosition(ofToFloat(columna[0][6]), ofToFloat(columna[0][7]), ofToFloat(columna[0][8]));
    pointLight2.setPosition(ofToFloat(columna[6][6]), ofToFloat(columna[6][7]), ofToFloat(columna[6][8]));
    pointLight3.setPosition(ofToFloat(columna[8][6]), ofToFloat(columna[8][7]), ofToFloat(columna[8][8]));

    //pointLight.setPosition((ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.5)*(ofGetWidth()*.3), ofGetHeight()/2, 500);

    //pointLight2.setPosition();
    //pointLight3.setPosition();
    
  camera.orbit(ofGetElapsedTimef()*2, ofGetElapsedTimef()*10, camera.getDistance(), ofVec3f(0, 0, 0));
    
  while (reciever.hasWaitingMessages()){
    ofxOscMessage m;
    reciever.getNextMessage(&m); 
      if (m.getAddress() == "/star" && m.getNumArgs() == 1){
          //camera.lookAt(nodos[m.getArgAsInt(0)]);
          prueba = m.getArgAsString(0);
          int paso2 = m.getArgAsInt(0) * 3;
          string fuenteNombre = ofToString(filas[paso2+1]) + " " + ofToString(filas[paso2+2]); // +3 para imprimir los valores de las fuentes. Empieza en 1, 0 es header.
          posicionX = " l=" + ofToString(columna[ofToInt(prueba)][1]);
          posicionY = " b=" + ofToString(columna[ofToInt(prueba)][2]) + " RA=" + ofToString(columna[ofToInt(prueba)][3]) + " Dec=" + ofToString(columna[ofToInt(prueba)][4]);
          mapa.load("maps/"+ofToString(m.getArgAsInt(0)+1)+".png");
          //posicionZ = " z = " + ofToString(columna[ofToInt(prueba)][8]);
      }
      if (m.getAddress() == "/crabSend" && m.getNumArgs() == 1){
          intensidad = m.getArgAsFloat(0);
      }
      if (m.getAddress() == "/mkr421Send" && m.getNumArgs() == 1){
          intensidad = m.getArgAsFloat(0);
      }
      if (m.getAddress() == "/mkr501Send" && m.getNumArgs() == 1){
          intensidad = m.getArgAsFloat(0);
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
   // ofEnableLighting();
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
    ofSetColor(255);
    //ofSetColor(102, 255, 102);
    ofEnableLighting();
    //pointLight.draw();
    //pointLight2.draw();
    //pointLight3.draw();
    pointLight.enable();
    pointLight2.enable();
    pointLight3.enable();
    glLineWidth(1);

    //material.begin();

    for (int i = 0;i < 39;i++){
        fuentes[i].setPosition(ofToFloat(columna[i][6]), ofToFloat(columna[i][7]), ofToFloat(columna[i][8]));
        ofSetColor(255);
        //float intensilocal = ofMap(intensidad, 0, 0.06, 0, 255);
        //ofSetColor(intensilocal, intensilocal, intensilocal);
        //scale = scale*0.9 + newScale*0.1; // para smoothear?
        //fuentes[i].setRadius(valorFuente);
        fuentes[i].draw();
        ofSetColor(255.f, 113.f, 206.f, 180);
        fuentes[8].draw();
        ofSetColor( 1.f, 205.f, 254.f, 180 );
        fuentes[6].draw();
        ofSetColor(185.f, 103.f, 255.f, 180);
        fuentes[0].draw();
    }
    
    float intensilocal = ofMap(intensidad, 0.0, 0.04, 0.0, 1.0);
    
    colorLight1 = ofColor(255.f*intensilocal, 113.f*intensilocal, 206.f*intensilocal );
    colorLight2 = ofColor( 1.f*intensilocal, 205.f*intensilocal, 254.f*intensilocal );
    colorLight3 = ofColor(185.f*intensilocal, 103.f*intensilocal, 255.f*intensilocal );
    
    pointLight.setDiffuseColor( colorLight1 );
    pointLight.setSpecularColor( colorLight1 );
    pointLight2.setDiffuseColor( colorLight2 );
    pointLight2.setSpecularColor( colorLight2 );
    pointLight3.setDiffuseColor( colorLight3 );
    pointLight3.setSpecularColor( colorLight3 );

    ofFill();
    
    ofSetColor(255, 255, 255);
    
    for (int i = 0;i < 500;i++){
        ofPushMatrix();
        ofRotateZ(ofGetElapsedTimef()+10);
        
        ofTranslate((ofNoise(i/2.4)-0.5)*1600,
                    (ofNoise(i/5.6)-0.5)*1600,
                    (ofNoise(i/8.2)-0.5)*1600);
        
        ofSphere(0, 0, (ofNoise(i/3.4)-0.1)*1);
        ofPopMatrix();
    }

    ofSetColor(255, 255, 255);

    sphere.drawWireframe();
    
    material.begin();
    sphere2.drawWireframe();
    material.end();
    
   // material.end();
    camera.end();
    
    ofDisableLighting();
    ofDisableDepthTest();
    
    ofSetColor(255);
    //ofSetColor(102, 255, 102);
    font.drawString( "nombre="+posicionX + posicionY + posicionZ + prueba, 20, 20);
    font.drawString("Curva de Luz: Crab"+crabo, 20, 40);
    font.drawString( "ofhawc> " + typing, 20, 60);

    ofNoFill();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofDrawLine(-ofGetWidth()/64, 0, ofGetWidth()/64,0);
    ofDrawLine(0, -ofGetWidth()/64, 0, ofGetWidth()/64);
    //ofSetColor(200, 200, 200);
    mapa.draw(ofGetWidth()/2-125, ofGetHeight()/2-110, 300, 225);
    //ofSetColor(102, 255, 102);
    
    ofSetRectMode(OF_RECTMODE_CORNER);

    //ofTranslate(ofGetWidth()/2, -ofGetHeight());



}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // if we didn't hit return, add the key to our string
    if(key != OF_KEY_RETURN){
        // some trickery: ignore the backspace key
        if(key != OF_KEY_BACKSPACE){
            typing += key;
        }
        else{
            if(typing.size() > 0){
                typing.erase(typing.end() - 1);
            }
        }
    }

    else{
        std::vector < std::string > textAnalisis = ofSplitString(typing, " ");
        if(textAnalisis[0] == "fuente"){
            int mapps = ofToInt(textAnalisis[1]) + 1;
            mapa.load("maps/"+ ofToString(mapps)+".png");
            pruebaInt = ofToInt(textAnalisis[1]);
            prueba = ofToString(textAnalisis[1]);
            posicionX = " l=" + ofToString(columna[ofToInt(prueba)][1]);
            posicionY = " b=" + ofToString(columna[ofToInt(prueba)][2]) + " RA=" + ofToString(columna[ofToInt(prueba)][3]) + " Dec=" + ofToString(columna[ofToInt(prueba)][4]);
            mapa.load("maps/"+ofToString(ofToInt(textAnalisis[1])+1)+".png");
            ofxOscMessage m;
            m.setAddress("/star");
            int numcrab = ofToInt(textAnalisis[1]);
            m.addIntArg(numcrab);
            sender.sendMessage(m, false);
        }
        typing = "";
    }
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
