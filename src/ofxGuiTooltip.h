//
//  ofxGuiTooltip.h
//
//  Created by Roy Macdonald on 10/29/22.
//

#pragma once
#include "ofMain.h"
#include "ofxGui.h"


class ofxGuiTooltip{
public:
    
    
    
    
    static ofxBaseGui* findOverGui(ofxGuiGroup* group, float x, float y);
    

    void registerGui(ofxGuiGroup* group, const string& stringsFilepath, const string& jsonSubPath = "");
    void unregisterGui(ofxGuiGroup* group);
    
    void clear();
    
    
    
    void draw();
    
    bool isEnabled();
    void enable();
    void disable();
    
    
    
private:

    void getGuiControlPaths(ofxGuiGroup* group, ofJson &json, string prefix = "");
    
    
    void registerMouse();
    void unregisterMouse();
    
    ofEventListeners listeners;
    
    void mouseOver(ofMouseEventArgs&);
    
    bool bMouseRegistered = false;

    vector<ofxGuiGroup*> guis;

    ofxBaseGui * overGui = nullptr;
    
    string currentTooltip = "";
    
    map<ofxBaseGui*, string> tooltipsMap;
    
    bool bIsEnabled = false;

    void getSetTooltip(ofxBaseGui* gui, ofJson &json, bool bIsGroup = false);
    
};
