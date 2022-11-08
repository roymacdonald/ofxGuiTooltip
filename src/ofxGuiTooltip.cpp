//
//  ofxGuiTooltip.cpp
//
//  Created by Roy Macdonald on 10/29/22.
//


#include "ofxGuiTooltip.h"


void ofxGuiTooltip::getSetTooltip(ofxBaseGui* gui, ofJson &json, bool bIsGroup){
    if(gui){
        
        string name = gui->getName();
        if(bIsGroup){
            name = "tooltip";
        }

#ifdef USE_OFX_DROPDOWN
        ofxDropdownOption * d = dynamic_cast<ofxDropdownOption*>(gui);
        if(d){
            d->setupTooltip(json);
            auto it = find (dropDowns.begin(), dropDowns.end(), d);
            if (it == dropDowns.end()){
                dropDowns.push_back(d);
            }
            
        }else{
#endif
        static ofBitmapFont bf;
        if(json.contains(name)){
            json.at(name).get_to(tooltipsMap[gui].text);
            tooltipsMap[gui].boundingBox = bf.getBoundingBox(tooltipsMap[gui].text, 0,0);
        }else{
            json[name] = "";
        }
#ifdef USE_OFX_DROPDOWN
        }
#endif
        
    }
}

//---------------------------------------------------------------------

void ofxGuiTooltip::getGuiControlPaths(ofxGuiGroup* group, ofJson &json){
    if(group == nullptr){
        return;
    }
    
    
    auto n = group->getNumControls();
    try
    {

        getSetTooltip(group, json, true);
        
        for(size_t i = 0; i < n; i++){
            ofxBaseGui* c = group->getControl(i);
            if(c){
                
                ofxGuiGroup * g = dynamic_cast<ofxGuiGroup*>(c);
                if(g){
                    getGuiControlPaths(g,  json["group"][c->getName()]);
                }else{
                    getSetTooltip(c, json["group"]);
                }
            }
        }
    }
    catch (ofJson::exception& e)
    {
        // output exception information
        ofLogWarning("ofxGuiTooltip::getGuiControlPaths") << "exeption (" << e.id << ") thrown: " << e.what() ;
        
    }
}

ofxBaseGui* ofxGuiTooltip::findOverGui(ofxGuiGroup* group, float x, float y){
    if(group == nullptr){
        return nullptr;
    }
    ofRectangle shape = group->getShape();
    if(shape.inside(x, y) == false){
        return nullptr;
    }
    if(group->isHeaderEnabled()){
        shape.height = ofxBaseGui::isHiDpiEnabled()?36:18;
        if(shape.inside(x, y)){
            return static_cast<ofxBaseGui*>(group);
        }
    }
    
    auto n = group->getNumControls();
    
    for(size_t i = 0; i < n; i++){
        ofxBaseGui* c = group->getControl(i);
        if(c){
            if(c->getShape().inside(x, y)){
                ofxGuiGroup * g = dynamic_cast<ofxGuiGroup*>(c);
                if(g){
                    return findOverGui(g, x, y);
                }
                return c;
            }
        }
    }
    return nullptr;
}

//---------------------------------------------------------------------
void ofxGuiTooltip::registerGui(ofxGuiGroup* group, const string& stringsFilepath, const string& jsonSubPath){

    addGuiGroup(group);
    ofJson json;
    if(ofFile::doesFileExist(stringsFilepath)){
        json = ofLoadJson(stringsFilepath);
    }
    
    getGuiControlPaths(group, (jsonSubPath.empty())?json:json[ofJson::json_pointer(jsonSubPath)]);
//    if(!jsonSubPath.empty()){
        ofSavePrettyJson(stringsFilepath, json);
//    }
    enable();
}

//---------------------------------------------------------------------
void ofxGuiTooltip::eraseFromTooltipsMap(ofxBaseGui* g){
    if(!g)return;
    
    ofxGuiGroup * group = dynamic_cast<ofxGuiGroup*>(g);
    if(group){
        size_t n = group->getNumControls();
        for(size_t i = 0; i < n ; i ++){
            eraseFromTooltipsMap(group->getControl(i));
        }
    }else{
        if(tooltipsMap.count(g)){
            tooltipsMap.erase(g);
        }
    }
}

//---------------------------------------------------------------------
void ofxGuiTooltip::unregisterGui(ofxGuiGroup* group){
    size_t n = guis.size();
    ofRemove(guis, [group](GuiGroupPointers& g){
        return g.gui == group;
    });
    
    if(n != guis.size()){
        eraseFromTooltipsMap(group);
    }
    
    if(guis.size() == 0){
        disable();
    }
}

//---------------------------------------------------------------------
void ofxGuiTooltip::clear(){
    guis.clear();
}

//---------------------------------------------------------------------
void ofxGuiTooltip::draw(){
    if(bIsEnabled){
        if(overGui){
            float x = ofGetMouseX();
            float y = ofGetMouseY();
            if(!currentTooltip.text.empty()){
                if(x > ofGetWidth() - currentTooltip.boundingBox.width){
                    x = ofGetWidth() - currentTooltip.boundingBox.width;
                }
                y = y - currentTooltip.boundingBox.y + 20;
                
                ofDrawBitmapStringHighlight(currentTooltip.text, x, y , ofColor::lightYellow, ofColor::black);
            }
        }
#ifdef USE_OFX_DROPDOWN
        for(auto d: dropDowns){
            if(d){
                d->drawTooltip();
            }
        }
#endif
    }
}

//---------------------------------------------------------------------
void ofxGuiTooltip::registerMouse(){
    if(!bMouseRegistered){
        bMouseRegistered = true;
        listeners.push(ofEvents().mouseMoved.newListener(this, &ofxGuiTooltip::mouseOver, -1000));
    }
}

//---------------------------------------------------------------------
void ofxGuiTooltip::unregisterMouse(){
    if(bMouseRegistered){
        bMouseRegistered = false;
        listeners.unsubscribeAll();
    }
}

//---------------------------------------------------------------------
void ofxGuiTooltip::mouseOver(ofMouseEventArgs& args){
    
    auto x = args.x;
    auto y = args.y;
    
    auto prevOverGui = overGui;
    overGui = nullptr;

    currentTooltip.clear();
    for(auto& g : guis){
        if(g.gui){
            auto c = findOverGui(g.gui, x,y);
            if(c){
                overGui = c;
                if(tooltipsMap.count(overGui)){
                    currentTooltip = tooltipsMap[overGui];
                }
                break;
            }
        }
    }
}
//---------------------------------------------------------------------
bool ofxGuiTooltip::isEnabled(){
    return bIsEnabled;
}
//---------------------------------------------------------------------
void ofxGuiTooltip::enable(){
    bIsEnabled = true;
    registerMouse();
#ifdef USE_OFX_DROPDOWN
        for(auto d: dropDowns){
            if(d){
                d->enableTooltip();
            }
        }
#endif

}
//---------------------------------------------------------------------
void ofxGuiTooltip::disable(){
    bIsEnabled = false;
    unregisterMouse();
#ifdef USE_OFX_DROPDOWN
        for(auto d: dropDowns){
            if(d){
                d->disableTooltip();
            }
        }
#endif
}
    //---------------------------------------------------------------------
bool ofxGuiTooltip::addGuiGroup(ofxGuiGroup* group, bool bIsDropdown){
    bool bFound = false;
    for(auto &g : guis){
        if(g.gui && g.gui == group){
            bFound = true;
            return false;
        }
    }
    if(!bFound){
        guis.push_back(GuiGroupPointers());
        guis.back().gui = group;
        guis.back().bIsDropdown = bIsDropdown;
        return true;
    }
    return false;
}
