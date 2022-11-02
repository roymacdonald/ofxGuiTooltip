#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

    gui.setup("GUI");
    size_t p_count = 0;
    size_t g_count = 0;
    groups.push_back(ofParameterGroup("Group " + ofToString(g_count)));
    for(size_t i = 0; i < 40; i++){

        floats.push_back({"param "+ofToString(i), 0, 0,1});
        
        if(ofRandom(1) > 0.8){
            g_count ++;
            groups.push_back(ofParameterGroup("Group " + ofToString(g_count)));
            groups[g_count - 1].add(groups[g_count ]);
        }
        groups[g_count].add(floats.back());
    }
    gui.add(groups[0]);
    
    tooltips.registerGui(&gui, "tooltips.json");
    
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    gui.draw();
    tooltips.draw();
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
