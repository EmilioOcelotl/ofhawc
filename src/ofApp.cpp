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

  camera.setDistance(200); 

  // obj

  sphere.setRadius(1000);

  for(int i = 0; i < LIM; i++){
    //objstrings[LIM];
    //fontobj[LIM];
  }

  // bools

  spheremode = true;
  domemode = false;

  // OSC

  sender.setup("127.0.0.1", 5613);
  reciever.setup(5612);

  // XML

  //XML.load ("xml/hawc.xml");

  // dome
  
  domemaster.setup();
  domemaster.setCameraPosition(0,0,10);

  // fonts

  font.load("fonts/DejaVuSansMono.ttf", 40, true, true, true);
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

  // camera.orbit(ofGetElapsedTimef()*2, ofGetElapsedTimef(), camera.getDistance(), ofVec3f(0, 0, 0));

  while (reciever.hasWaitingMessages()){
    ofxOscMessage m;
    reciever.getNextMessage(&m);
  }  
}

//--------------------------------------------------------------
void ofApp::draw(){

  ofEnableDepthTest();    
  ofSetRectMode(OF_RECTMODE_CENTER);

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

  // font.drawString(text, ofGetWidth()/2, ofGetHeight()/2);

  camera.begin();

  if(spheremode == true){
    
  sphere.drawWireframe();
  
  ofEnableLighting();
  pointLight.draw();
  //pointLight2.draw();
  //pointLight3.draw();
  pointLight.enable();
  //pointLight2.enable();
  //pointLight3.enable();
  material.begin();

  //ofTranslate(ofGetWidth()/2, ofGetHeight()/2); 
  // sphere.drawWireframe();

  ofSetColor(255, 255, 55, 25);
  
        for (int i = 0;i < 39;i++){
            ofPushMatrix();
            ofRotateZ(ofGetElapsedTimef()+10);
            
            ofTranslate((ofNoise(i/2.4)-0.5)*2000,
                        (ofNoise(i/5.6)-0.5)*2000,
                        (ofNoise(i/8.2)-0.5)*2000);
            ofSphere(0, 0, 10);
            ofPopMatrix();
        }

  material.end();

  camera.end();

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
