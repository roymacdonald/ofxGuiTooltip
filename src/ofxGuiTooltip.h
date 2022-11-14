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
    
    ///\Recursively find the gui element over which the x and y coordinates are.
    ///\param group the ofxGuiGroup that will be scanned and check if the coordinates are over it or one of its children.
    ///\param x the x axis coordinate to check
    ///\param y the y axis coordinate to check
    ///\return pointer to the element that is under the x and y coordinates
    static ofxBaseGui* findOverGui(ofxGuiGroup* group, float x, float y);

    ///\brief register an ofxGuiGroup and set its tooltips from a json file. This function will scan all over the guigroup and see if there are any tooltips for its elements in the json file
    ///\param group the gui group which will be scanned and add tooltips from it.
    ///\param jsonFilepath the filepath to the json file that contains the tooltips texts. If no json file is found a new one will be created. If in the json file there is no tooltip for a gui element, the json file will be populated and saved so you can then open it and add the texts to it. super handy.
    ///\param jsonSubPath if not an empty string this will be used to set the json root from where to start scanning. This can be useful if you want to have several ofxGuiTooltip instances but you want to have all in a single json file
    void registerGui(ofxGuiGroup* group, const string& jsonFilepath, const string& jsonSubPath = "");
    
    
    ///\brief unregister (remove) a gui group that was previously registered with registerGui(...)
    ///\param group the group to remove
    void unregisterGui(ofxGuiGroup* group);
    

    ///\brief clear everything.
    void clear();
    
    ///\brief draw the tooltips
    /// make sure you place this after drawing the gui, otherwise the tooltips will show under the gui
    void draw();
    
    
    ///\brief enable tooltips
    ///Only when enabled the tooltips will get drawn and will catch mouse events.
    void enable();
    ///\brief disable tooltips
    void disable();
    ///\brief check if the tooltips are enabled
    ///\return true if enabled, false otherwise
    bool isEnabled();
    
    
    ///\brief add a tooltip to an ofParameter that is part of the passed ofxGuiGroup. The group will be scanned for the passed ofParameter so it does not matter if it is nested inside of it.
    ///\param group ofxGuiGroup that will be scanned for the gui element that corresponds to the passed param
    ///\param param ofParameter or ofParameterGroup used to generate a gui element inside of the passed ofxGuiGroup.
    ///\param tooltip_text the text to be show as a tooltip
    
    void add(ofxGuiGroup* group, ofAbstractParameter& param,  const string& tooltip_text);

    ///\brief add a tool tip to an ofxGui element
    ///\param gui a pointer to an ofxGui element, or any that inherits from ofxBaseGui
    ///\param tooltip_text the text to be show as a tooltip
    ///it is necesary that the gui object passed belongs to an ofxGuiGroup that has been already registered either using the registerGui(...) or addGuiGroup(...) functions
    void add(ofxBaseGui* gui, const string& tooltip_text);
    
protected:
    
    bool addGuiGroup(ofxGuiGroup* group);
    
    struct TooltipData{
        ofRectangle boundingBox;
        string text;
        void clear(){
            boundingBox.set(0,0,0,0);
            text = "";
        }
    };
    
    
private:
    

    
    void getGuiControlPaths(ofxGuiGroup* group, ofJson &json);

    
    void registerMouse();
    void unregisterMouse();
    
    ofEventListeners listeners;
    
    void mouseOver(ofMouseEventArgs&);
    
    bool bMouseRegistered = false;

    vector<ofxGuiGroup*> guis;

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
