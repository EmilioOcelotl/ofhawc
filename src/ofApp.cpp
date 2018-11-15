/*
 
 ofhawc
 
 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetWindowTitle("ofhawc");
    ofBackground(0);
    ofSetColor(255);
    ofSetFrameRate(60);
    ofSetWindowShape(1360, 768); /// La resolución de la pantalla final
    ofHideCursor();
    
    // camera
    
    camera.setDistance(100);
    prueba = "2HWC J0534+220 l=184.546552486 b=-5.78316902994 RA=83.6279 Dec=22.0243";
    //prueba = "0";
    pruebaInt = 0;
    fuenteObservada = 0;
    //camera.setPosition(0, 0, 0);
    
    // orbit
    
    orbitX = 0;
    orbitY = 0;
    
    // obj
    
    sphere.setRadius(200);
    //sphere.setResolution();
    sphere2.setRadius(20);
    sphere3.setRadius(100);
    //sphere3.setResolution(5);
    mapa.load("maps/1.png");
    typing = "";
    post = "ofhawc | h + ENTER para ayuda";
    intensidadCrab = 0.01241282988032;
    intensidadMkr421 = 0.01241282988032;
    intensidadMkr501 = 0.01241282988032;
    
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
    
    //sender.setup("192.168.1.67", 57120);
    sender.setup("127.0.0.1", 57120);
    reciever.setup(5612);
    
    // Syphon
    
#if (defined(__APPLE__) && defined(__MACH__))
    client.setup();
    syphonON = 1;
#endif
    ofmode = 1;
    
    // fonts
    
    font.load("fonts/DejaVuSansMono.ttf", 14, true, true, true);
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
    //colorLight3 = ofColor(clR[2], clG[2], clB[2]); hola eric como estas todo lo qeu escribo aqui aparece alla
    
    colorLight1 = ofColor(255.f, 255, 255);
    colorLight2 = ofColor( 1.f, 205.f, 254.f );
    colorLight3 = ofColor(185.f, 103.f, 255.f);
    
    pointLight.setDiffuseColor( colorLight1 );
    pointLight.setSpecularColor( colorLight1 );
    pointLight2.setDiffuseColor( colorLight2 );
    pointLight2.setSpecularColor( colorLight2 );
    pointLight3.setDiffuseColor( colorLight3 );
    pointLight3.setSpecularColor( colorLight3 );
    
    ofSetSmoothLighting(true);
    
    material.setShininess( 120 );
    material.setSpecularColor(ofColor(255, 255, 255, 255));
    
    // datos //
    
    // posiciones
    
    std::vector < std::string > filas = ofSplitString(buffer.getText(), " ");
    fuenteNombre = ofToString(filas[4]) + " " + ofToString(filas[5]); // +3 para imprimir los valores de las fuentes. Empieza en 1, 0 es header.
    for (int i = 0;i < 39;i++){
        int paso = (i+1) * 3;
        columna[i] = ofSplitString(filas[paso], ",");
        nodos[i].set(ofToFloat(columna[i][6]), ofToFloat(columna[i][7]), ofToFloat(columna[i][8]) );
    }
    
    //crabo = " " + curvasDeLuz[1][2] + curvasDeLuz[2][5] + curvasDeLuz[1][8];
    
    //fbo mini ventana
    
    //fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F_ARB, 8);
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB, 8);
    
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();
    
    blur = 0;
    
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
    
    centro = 0;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofEnableAlphaBlending();
    ofEnableArbTex();
    //ofSetRectMode(OF_RECTMODE_CORNER);
    
    //camera.setPosition(0, 0, 0);
    
    // video //
    
    //ofSetRectMode(OF_RECTMODE_CENTER);
    // ofEnableLighting();
    //ofEnableArbTex();
    //fDisableAlphaBlending();
    //ofEnableDepthTest();
    //lets draw some graphics into our two fbos
    fbo.begin();
    drawScene();
    fbo.end();
    
    pointLight.setPosition(ofToFloat(columna[0][6]), ofToFloat(columna[0][7]), ofToFloat(columna[0][8]));
    pointLight2.setPosition(ofToFloat(columna[6][6]), ofToFloat(columna[6][7]), ofToFloat(columna[6][8]));
    pointLight3.setPosition(ofToFloat(columna[8][6]), ofToFloat(columna[8][7]), ofToFloat(columna[8][8]));
    
    //pointLight.setPosition((ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.5)*(ofGetWidth()*.3), ofGetHeight()/2, 500);
    
    //pointLight2.setPosition();
    //pointLight3.setPosition();
    
    camera.orbit(ofGetElapsedTimef()*orbitX, ofGetElapsedTimef()*orbitY, camera.getDistance(), ofVec3f(0, 0, 0));
    
    while (reciever.hasWaitingMessages()){
        ofxOscMessage m;
        reciever.getNextMessage(&m);
        if (m.getAddress() == "/fuente" && m.getNumArgs() == 1){
            //camera.lookAt(nodos[m.getArgAsInt(0)]);
            prueba = m.getArgAsString(0);
            fuenteObservada = m.getArgAsInt(0);
            int paso2 = m.getArgAsInt(0) * 3;
            string fuenteNombre = ofToString(filas[paso2+1]) + " " + ofToString(filas[paso2+2]); // +3 para imprimir los valores de las fuentes. Empieza en 1, 0 es header.
            posicionX = " l=" + ofToString(columna[ofToInt(prueba)][1]);
            posicionY = " b=" + ofToString(columna[ofToInt(prueba)][2]) + " RA=" + ofToString(columna[ofToInt(prueba)][3]) + " Dec=" + ofToString(columna[ofToInt(prueba)][4]);
            mapa.load("maps/"+ofToString(m.getArgAsInt(0)+1)+".png");
            //posicionZ = " z = " + ofToString(columna[ofToInt(prueba)][8]);
        }
        if (m.getAddress() == "/crabSend" && m.getNumArgs() == 1){
            intensidadCrab = m.getArgAsFloat(0);
        }
        if (m.getAddress() == "/mrk421Send" && m.getNumArgs() == 1){
            intensidadMkr421 = m.getArgAsFloat(0);
        }
        if (m.getAddress() == "/mrk501Send" && m.getNumArgs() == 1){
            intensidadMkr501 = m.getArgAsFloat(0);
        }
#if (defined(__APPLE__) && defined(__MACH__))
        if (m.getAddress() == "/ofmode" && m.getNumArgs() == 1){
            ofmode = m.getArgAsInt(0);
        }
#endif
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0, 0, 0);
    
    ofSetColor(255,255,255);
    
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

    fbo.draw(0,-22);
    
    if(centro == 0 ){
    camera.lookAt(nodos[fuenteObservada]);
    }
    
    if(centro == 1){
        ofVec3f centro;
        centro.set(0, 0, 0);
        camera.lookAt(centro);
    }
    //drawScene();
    
    ofTranslate(0, 0, 0);

    ofSetRectMode(OF_RECTMODE_CORNER);
    ofSetColor(255);
    //ofSetColor(102, 255, 102, 200);
    ofScale(1, 1, 1);
    font.drawString( "Posición de la fuente enfocada en coordenadas esféricas", 20, 30);
    font.drawString( posicionX + posicionY + posicionZ + prueba, 50, 60);
    font.drawString("Curvas de Luz", 20, 90);
    font.drawString(" Crab   Mrk421  Mrk501"+crabo, 50, 180);
    
    font.drawString( "ofhawc> " + typing, 20, 210);
    //font.drawString(post, 20, 240);
    
    ofNoFill();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofDrawLine(-ofGetWidth()/64, 0, ofGetWidth()/64,0);
    ofDrawLine(0, -ofGetWidth()/64, 0, ofGetWidth()/64);
    ofSetColor(200, 200, 200);
    ofSetRectMode(OF_RECTMODE_CORNER);
    //mapa.draw(ofGetWidth()/2-120, ofGetHeight()/2-610, 300, 225);
    mapa.draw(ofGetWidth()/2-275, -ofGetHeight()/2, 300, 225);
    
    //ofSetColor(102, 255, 102);
    ofSetRectMode(OF_RECTMODE_CORNER);
    
    float radioCrab = ofMap(intensidadCrab, 0.0011980022099968, 0.01241282988032, 0.0, 10.0);
    float radioMkr421 = ofMap(intensidadMkr421, 0.0011980022099968, 0.01241282988032, 0.0, 10.0);
    float radioMkr501 = ofMap(intensidadMkr501, 0.0011980022099968, 0.01241282988032, 0.0, 10.0);
    
    ofFill();
    ofSetColor(255.f, 113.f, 206.f);
    ofCircle(-ofGetWidth()/2+85, -ofGetHeight()/2+130, radioCrab);
    ofSetColor( 1.f, 205.f, 254.f);
    ofCircle(-ofGetWidth()/2+175, -ofGetHeight()/2+130, radioMkr421);
    ofSetColor(185.f, 103.f, 255.f);
    ofCircle(-ofGetWidth()/2+265, -ofGetHeight()/2+130, radioMkr501);

    
}

//--------------------------------------------------------------
void ofApp::drawScene(){
    
    
    ofDisableArbTex();
    ofEnableAlphaBlending();
    
    //ofTranslate(0, 50, 0);
    
    if(blur == 1){
        ofDisableDepthTest();
        ofFill();
        ofSetColor(0,0,0, 100);
        ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
        
        //2 - Draw graphics
        
        ofNoFill();
        ofSetColor(255,255,255);
        
    }
    
    if(blur == 0){
        ofEnableDepthTest();
        ofClear(0);
    }
    
    if(ofmode == 1){
        
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
        glLineWidth(0.5);
        
        //ofSetColor(102, 255, 102, 55);
        ofSetColor(255, 255);
        sphere.drawWireframe();
        
        material.begin();
        
        //ofSetColor(102, 255, 102, 200);
        
        //ofEnableDepthTest();
        
        for (int i = 0;i < 39;i++){
            fuentes[i].setPosition(ofToFloat(columna[i][6]), ofToFloat(columna[i][7]), ofToFloat(columna[i][8]));
            //ofSetColor(255, 255);
            //float intensilocal = ofMap(intensidad, 0, 0.06, 0, 255);
            //ofSetColor(intensilocal, intensilocal, intensilocal);
            //scale = scale*0.9 + newScale*0.1; // para smoothear?
            //fuentes[i].setRadius(valorFuente);
            float radioCrab = ofMap(intensidadCrab, 0.0011980022099968, 0.01241282988032, 0.0, 5.0);
            float radioMkr421 = ofMap(intensidadMkr421, 0.0011980022099968, 0.01241282988032, 0.0, 5.0);
            float radioMkr501 = ofMap(intensidadMkr501, 0.0011980022099968, 0.01241282988032, 0.0, 5.0);
            
            fuentes[i].draw();
            
            fuentes[0].setRadius(radioCrab);
            fuentes[8].setRadius(radioMkr421);
            fuentes[6].setRadius(radioMkr501);
            
        }
        
        float colorCrab = ofMap(intensidadCrab, 0.0011980022099968, 0.01241282988032, 0.0, 10.0);
        float colorMkr421 = ofMap(intensidadMkr421, 0.0011980022099968, 0.01241282988032, 0.0, 10.0);
        float colorMkr501 = ofMap(intensidadMkr501, 0.0011980022099968, 0.01241282988032, 0.0, 10.0);
        
        colorLight1 = ofColor(255.f*colorCrab, 113.f*colorCrab, 206.f*colorCrab );
        colorLight2 = ofColor( 1.f*colorMkr421, 205.f*colorMkr421, 254.f*colorMkr421 );
        colorLight3 = ofColor(185.f*colorMkr501, 103.f*colorMkr501, 255.f*colorMkr501 );
        
        pointLight.setDiffuseColor( colorLight1 );
        pointLight.setSpecularColor( colorLight1 );
        pointLight2.setDiffuseColor( colorLight2 );
        pointLight2.setSpecularColor( colorLight2 );
        pointLight3.setDiffuseColor( colorLight3 );
        pointLight3.setSpecularColor( colorLight3 );
        
        ofFill();
        
        ofSetColor(255, 255, 255, 50);
        
        for (int i = 0;i < 500;i++){
            ofPushMatrix();
            //ofRotateZ(ofGetElapsedTimef()+10);
            
            ofTranslate((ofNoise(i/2.4)-0.5)*600,
                        (ofNoise(i/5.6)-0.5)*600,
                        (ofNoise(i/8.2)-0.5)*600);
            
            ofSphere(0, 0, (ofNoise(i/3.4)-0.1)*0.5);
            ofPopMatrix();
        }
        
        //ofEnableDepthTest();
        sphere2.draw();
        ofSetColor(255, 255, 255, 200);
        sphere3.drawWireframe();
        material.end();
        
        camera.end();
        
    }
    
    ofDisableLighting();
    ofDisableDepthTest();
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofTranslate(0, ofGetHeight()/2+70);
    
    if(ofmode == 1){
        miniWin();
    };
    
    // esto tiene que ir al frente
    
#if (defined(__APPLE__) && defined(__MACH__))
    
    if(ofmode == 0){
        ofSetRectMode(OF_RECTMODE_CORNER);
        ofSetColor(255);
        ofTranslate(0, 0);
        client.draw(0, 0);
        ofTranslate(0, 0, 0);
        
        ofSetRectMode(OF_RECTMODE_CENTER);
    };
    
#endif
    
    
    
}


//--------------------------------------------------------------
void ofApp::miniWin(){ // pendiente dibujar la otra miniwin
 
    if(ofmode == 1){
        ofScale(0.5, 0.5, 0.5);
        ofSetRectMode(OF_RECTMODE_CORNER);
        ofSetColor(255);
        client.draw(0, 0);
    };

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
        
        if(textAnalisis[0] == "fuente" && ofToInt(textAnalisis[1]) < 39){
            centro = 0;
            int mapps = ofToInt(textAnalisis[1]) + 1;
            mapa.load("maps/"+ ofToString(mapps)+".png");
            pruebaInt = ofToInt(textAnalisis[1]);
            prueba = ofToString(textAnalisis[1]);
            int paso2 = ofToInt(textAnalisis[1]) * 3;
            fuenteObservada = ofToInt(textAnalisis[1]);
            //fuenteNombre = ofToString(filas[1]) + " " + ofToString(filas[2]); // +3 para imprimir los valores de las fuentes. Empieza en 1, 0 es header.
            posicionX = "Nombre="+fuenteNombre + " l=" + ofToString(columna[ofToInt(prueba)][1]);
            posicionY = " b=" + ofToString(columna[ofToInt(prueba)][2]) + " RA=" + ofToString(columna[ofToInt(prueba)][3]) + " Dec=" + ofToString(columna[ofToInt(prueba)][4]);
            mapa.load("maps/"+ofToString(ofToInt(textAnalisis[1])+1)+".png");
            ofxOscMessage m;
            m.setAddress("/star");
            int numcrab = ofToInt(textAnalisis[1]);
            m.addIntArg(numcrab);
            sender.sendMessage(m, false);
        }
        
        if(textAnalisis[0] == "ofmode"){
            ofmode = ofToInt(textAnalisis[1]);
        }
        
        if(textAnalisis[0] == "orbit"){
            orbitX = ofToInt(textAnalisis[1]);
            orbitY = ofToInt(textAnalisis[2]);
        }
        
        if(textAnalisis[0] == "centro"){
            centro = 1;
        }
        
        if (textAnalisis[0] == "glitch"){
            if(ofToInt(textAnalisis[1]) == 0 && ofToInt(textAnalisis[2]) == 0){
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
            }
            
            if(ofToInt(textAnalisis[2]) == 1){
                convergence = ofToBool(textAnalisis[1]);
            }
            
            if(ofToInt(textAnalisis[2]) == 2){
                glow = ofToBool(textAnalisis[1]);
            }
            
            if(ofToInt(textAnalisis[2]) == 3){
                shaker = ofToBool(textAnalisis[1]);
            }
            
            if(ofToInt(textAnalisis[2]) == 4){
                cutslider = ofToBool(textAnalisis[1]);
            }
            
            if(ofToInt(textAnalisis[2]) == 5){
                twist = ofToBool(textAnalisis[1]);
            }
            
            if(ofToInt(textAnalisis[2]) == 6){
                outline = ofToBool(textAnalisis[1]);
            }
            
            if(ofToInt(textAnalisis[2]) == 7){
                noise = ofToBool(textAnalisis[1]);
            }
            
            if(ofToInt(textAnalisis[2]) == 8){
                slitscan = ofToBool(textAnalisis[1]);
            }
            
            if(ofToInt(textAnalisis[2]) == 9){
                swell = ofToBool(textAnalisis[1]);
            }
            
            if(ofToInt(textAnalisis[2]) == 10){
                invert = ofToBool(textAnalisis[1]);
            }
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
