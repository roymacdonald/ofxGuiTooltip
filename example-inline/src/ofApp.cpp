#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

    gui.setup("GUI");

    groups.setName("Group 1");
    groups.add(floats1);
    groups.add(floats2);

    gui.add(groups);

    gui.add(slider1.setup("slider 1", 1, 0, 1));
    gui.add(slider2.setup("slider 2", 1, 0, 100));


    

    
    /// when you want to add a tooltip to an object that inherits from ofxBaseGui, thus all the ofxGui elements
    /// you just pass the gui element as a pointer, (notice the & preceding the first argument,) and the text you want to show when the mouse is over it
    tooltips.add(&slider1, "This is the tooltip for the slider 1");
    tooltips.add(&slider2, "This is the tooltip for the the other slider");

    
    
    ///when you want to use ofParameters you need to pass 3 arguments.
    ///first is a pointer to the guigroup of the Gui group over which you want to show the tooltips. Then the ofParameter asociated to the gui element and then the text that will be show as a tooltip
    tooltips.add(&gui, groups,"this is the group tooltip");
    tooltips.add(&gui, floats1, "Tooltip for floats1");
    tooltips.add(&gui, floats2, "Tooltip for floats2");
    
    
    // you need to enable, otherwise it wont draw nor receive mouse input
    tooltips.enable();
    
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
