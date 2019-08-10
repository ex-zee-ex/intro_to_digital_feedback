#pragma once

#include "ofMain.h"

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
    
    
    
    
    //declare our shader objects
    ofShader shader_Feedback;
    
    //declare our framebuffer objects
    
    //framebuffer0 is what we will use to draw to the screen
    ofFbo framebuffer0;
    
    //framebuffer1 is what we use to store a copy of whats drawn to the screen and then pass it back to the shaders for convolutions
    ofFbo framebuffer1;
    
		
};
