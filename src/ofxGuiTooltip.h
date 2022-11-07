//
//  ofxGuiTooltip.h
//
//  Created by Roy Macdonald on 10/29/22.
//

#pragma once
#include "ofMain.h"
#include "ofxGui.h"

#ifdef USE_OFX_DROPDOWN
#include "ofxDropdown.h"
#endif


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
    
    struct TooltipData{
        ofRectangle boundingBox;
        string text;
        void clear(){
            boundingBox.set(0,0,0,0);
            text = "";
        }
    };
    
    struct GuiGroupPointers{
        ofxGuiGroup* gui = nullptr;
        bool bIsDropdown = false;
    };
    
private:
    
    bool addGuiGroup(ofxGuiGroup* group, bool bIsDropdown = false);
    
    void getGuiControlPaths(ofxGuiGroup* group, ofJson &json);

    
    void registerMouse();
    void unregisterMouse();
    
    ofEventListeners listeners;
    
    void mouseOver(ofMouseEventArgs&);
    
    bool bMouseRegistered = false;

    vector<GuiGroupPointers> guis;

    ofxBaseGui * overGui = nullptr;
    
    TooltipData currentTooltip;
    
    map<ofxBaseGui*, TooltipData> tooltipsMap;
    
    void eraseFromTooltipsMap(ofxBaseGui* g);
    
    bool bIsEnabled = false;


    void getSetTooltip(ofxBaseGui* gui, ofJson &json, bool bIsGroup = false);

    
#ifdef USE_OFX_DROPDOWN
    vector<ofxDropdownOption *> dropDowns;
#endif
};
