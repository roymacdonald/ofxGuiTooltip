#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

    
    
    //Setup some gui elements. I just made this kinda randomly. It does not matter.
    //As long as you have a working ofxGui with whichever structure this will work.
    
    gui.setup("GUI");
    
    floats0.set("floats0", 1,0,1);
    floats1.set("floats1", 1,0,1);
    floats2.set("floats2", 1,0,1);
    floats3.set("floats3", 1,0,1);
    int0.set("int0", 1,0,100);
    color0.set("color0", 1,0,1);
    
    group0.setName("group0");
    group1.setName("group1");
    
    
    
    
    group0.add(floats0);
    group0.add(floats1);
    group1.add(color0);
    group1.add(int0);
    group0.add(group1);
    group0.add(floats2);
    
    gui.add(group0);
    gui.add(floats3);
    
    // -- tooltips.---
    // just call this single function and it is all you need to set these.
    //If the json file you specified does not exist a new one will be created.
    //If the json file does not contain the tooltip for a gui widget it will create it and store it back into the same file.
    //You dont need to worry about the json structure as it will ge automatically generated. Although, if you change the structure of the gui or even the names of the ofParameters you will need to edit the json file. You will see the newly added elements as empty strings.
    //when you first run this go and open the json file, and add the tooltips there
    tooltips.registerGui(&gui, "tooltips.json");
    
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    gui.draw();
    // remember to draw the tooltip AFTER the gui, otherwise it would get drawn under the gui.
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
