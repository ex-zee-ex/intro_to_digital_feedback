#include "ofApp.h"

//here will be some variables that we will use to use the keyboard to control aspects of the shader.  because they need to be accessed by draw() and keypressed() we declare them outside of both of those functions

float sx=.95;
float dc=1;
float fv=1;

//--------------------------------------------------------------
void ofApp::setup(){
    
    //syncs up the framerate with the refresh rate on monitor
    ofSetVerticalSync(true);
    
    //lets keep it at 60fps if possible
    ofSetFrameRate(60);
    
    //can set up a switch for this on and off which adds drastically different qualities to the feedback
    ofBackground(0);
    
    
    
    //load the shaders
    //the file path is automatically looking within the bin/data folder and needs to see shader_feedback.frag and shader_feedback.vert
    shader_Feedback.load("shadersGL2/shader_feedback");
    
    //allocate memory for the framebuffer objects
    
    //if you use ofGetWidth() etc for allocation then the framebuffer will only allocate memory for the size of the window declared over in main.cpp
    framebuffer0.allocate(ofGetWidth(), ofGetHeight());
    framebuffer1.allocate(ofGetWidth(), ofGetHeight());
    
    //if you want to have the ability to resize the window or fullscreen it while it is running then you can instead allocate enough memory for the entire screen.  i reccomend not doing this otherwise though because it can cause unnecessary slowdown to reserve huge chunks of gpu memory that wont be utilized
    // framebuffer0.allocate(ofGetScreenWidth(), ofGetScreenHeight());
    // framebuffer1.allocate(ofGetScreenWidth(), ofGetScreenHeight());
    
    
    //after allocating the memory we need to also clear the contents at those locations.  c++ does not automatically clear any memory for declared objects or variables so if you don't explicitly clear memory the framebuffers will load up with whatever stuff is just sitting in gpu memory so like bits and peices of desktop windows and browser stuff will pop up in a very glitchy way,
    
    framebuffer0.begin();
    ofClear(0,0,0,255);
    framebuffer0.end();
    
    framebuffer1.begin();
    ofClear(0,0,0,255);
    framebuffer1.end();
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //first we will draw everything to framebuffer0.  everything within the .begin() and .end() code will be drawn to the framebuffer0 object instead of sent to the screen
    
    framebuffer0.begin();
    
    
    //next we start running the shader code, all we are doing within the shader.begin() and .end() for this is pretty much just sending textures and variables to the shader to be processed within there
    shader_Feedback.begin();
    
    
    //when you draw a framebuffer or any other sort of texture within the shader.begin() and .end() zones that will automatically bind this texture to tex0 on the gpu
    framebuffer1.draw(0,0);
    
    //lets send a control for how strong we mix the feedback with the keyboard
    shader_Feedback.setUniform1f("mixxx",sx);
    
    //lets set up controls on how far we want our feedback to be displaced.  since we are going to be working with both an x and a y lets use a vector because that will make our shader code cleaner and possibly faster
    
    ofVec2f feedback_Displace;
    feedback_Displace.set(dc,fv);
    shader_Feedback.setUniform2f("feedback_Displace",feedback_Displace);
    
    shader_Feedback.end();
    
    
    //we need to have something to run feedback off of, so lets set up a rotating square here, after the shader code has exected and drawn but before we are done with drawing to the framebuffer
    
    //first fix up the coordinate system and rectmodes
    
    //we need to change rectmode to get it to rotate the way we want it too.  but we will need to change it back when we are done because changing rectmode also changes the way that framebuffers or any other object that gets drawn with a .draw() command will be drawn
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    //pushmatrix and popmatrix commands are used for when we want to do some linear transformations on the coordinate systems for just a specific block of code, like for example how to get a square in the center of the screen to spin around the z axis but without making everything else we draw stay still.  there are ways to do it without pushmatrix and translates but they are way bulkier code executions.  make sure that each pushmatrix has a corresponding popmatrix otherwise you will get errors.
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
    ofRotateZRad(ofGetElapsedTimef()/4);
    
    ofSetColor(255,127+127*sin(ofGetElapsedTimef()/8),255,255);
    ofNoFill();
    
    ofDrawRectangle(0,0,ofGetWidth()/8,ofGetWidth()/8);
    
    ofPopMatrix();
    
    //changing rectmode back to default
    ofSetRectMode(OF_RECTMODE_CORNER);
    
    
    framebuffer0.end();
    
    
    
    //___-_-_-_----__-_-_---_-___-
    
    //next we will draw framebuffer0 to the screen
    
    framebuffer0.draw(0,0);
    
    
    //__-_-_----_-___-_-_
    
    //next we draw framebuffer0 to framebuffer1 so that we can have feedback
    
    framebuffer1.begin();
    framebuffer0.draw(0,0);
    framebuffer1.end();
    
    
    //since we are changing some variables while playing with this code lets make sure to keep track of where these variables are at at any point by drawing them to the screen as well.  since we are drawing them here outside of any of the framebuffers they won't get processed in the feedback zones
        
        ofDrawBitmapString(" sx = "+ofToString(sx)+", dc = "+ofToString(dc)+", fv = "+ofToString(fv),10, ofGetHeight()-5 );

    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key=='s'){sx+=.01;}
    if(key=='x'){sx-=.01;}
    
    if(key=='d'){dc+=.01;}
    if(key=='c'){dc-=.01;}
    
    if(key=='f'){fv+=.01;}
    if(key=='v'){fv-=.01;}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
