//
//  ofxGuiTooltipBase.cpp
//  LidarSlam2
//
//  Created by Roy Macdonald on 17-11-22.
//

#include "ofxGuiTooltipBase.h"
#include "ofGraphics.h"
#include "ofBitmapFont.h"
#include "ofAppRunner.h"

//--------------------------------------------------------------
void ofxGuiTooltipBase::setupTooltip(const std::string& jsonFilePath){
    if(ofFile::doesFileExist(jsonFilePath)){
        setupTooltip(ofLoadJson(jsonFilePath));
    }
}

//--------------------------------------------------------------
void ofxGuiTooltipBase::setupTooltip(ofJson & json){
    if(!guiElement){
        ofLogWarning("ofxGuiTooltipBase::setupTooltip") << "guiElement is nullptr!";
        return;
    }
    removeTooltip();
    
    auto name = guiElement -> getName();
    if(json.contains(name)){
        setTooltipText(json[name]);
    }else{
        json[name] = "Tooltip . Change this text!";
    }
}

//--------------------------------------------------------------
void ofxGuiTooltipBase::setTooltipText(const std::string& text){
    tooltipText = text;
    ofBitmapFont bf;
    tooltipRect = bf.getBoundingBox(text, 0, 0);
}

//--------------------------------------------------------------
void ofxGuiTooltipBase::resetTooltips(){
    removeTooltip();
}

//--------------------------------------------------------------
void ofxGuiTooltipBase::removeTooltip(){
    disableTooltip();
    tooltipText = "";
    tooltipRect.set(0, 0, 0, 0);
}

//--------------------------------------------------------------
void ofxGuiTooltipBase::enableTooltip() {
    bTooltipsEnabled = true;
}

//--------------------------------------------------------------
void ofxGuiTooltipBase::disableTooltip() {
    bTooltipsEnabled = false;
}

//--------------------------------------------------------------
bool ofxGuiTooltipBase::isTooltipEnabled() {
    return bTooltipsEnabled;
}

//--------------------------------------------------------------
void ofxGuiTooltipBase::drawTooltip(){
    if(!guiElement )return;
    
    if( !isOver() || !bTooltipsEnabled ||
       tooltipText.empty()){
        return;
    }
    float x = ofGetMouseX();
    float y = ofGetMouseY();
    
    if(guiElement ->getShape().inside(x, y) == false) return;
    
           
    if(x > ofGetWidth() - tooltipRect.width){
        x = ofGetWidth() - tooltipRect.width;
    }
    y = y - tooltipRect.y + 20;
    
    ofDrawBitmapStringHighlight(tooltipText, x, y , ofColor::lightYellow, ofColor::black);
    
}

