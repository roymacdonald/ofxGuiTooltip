#pragma once


#include "ofMain.h"
#include "ofxGui.h"
#include "ofxGuiTooltip.h"


class ofApp: public ofBaseApp{
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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        
    ofxPanel gui;
    
    ofParameter<float> floats0;
    ofParameter<float> floats1;
    ofParameter<float> floats2;
    ofParameter<float> floats3;
    ofParameter<ofColor> color0;
    ofParameter<int> int0;
    ofParameterGroup group0;
    ofParameterGroup group1;
    
    ofxGuiTooltip tooltips;
    
		
};
