//
//  ofxGuiTooltip.cpp
//
//  Created by Roy Macdonald on 10/29/22.
//


#include "ofxGuiTooltip.h"

void ofxGuiTooltip::getSetTooltip(ofxBaseGui* gui, ofJson &json, bool bIsGroup){
    if(gui){
//        cout << "---------getSetTooltip-------------\n";
        
        string name = gui->getName();
        if(bIsGroup){
            name = "tooltip";
//            cout << "   group " << name << endl;
//            name += "_Gui_group_tooltip";
            if(json.contains(name)){
                json.at(name).get_to(tooltipsMap[gui]);
            }else{
                json[name] = "";
            }
        }else{
            if(json.contains(name)){
                json.at(name).get_to(tooltipsMap[gui]);
            }else{
                json[name] = "";
            }
        }
//        cout << json.dump(4) << endl;
//        if(json == nullptr){
//
//        }
        
        
    }
}

//---------------------------------------------------------------------
void ofxGuiTooltip::getGuiControlPaths(ofxGuiGroup* group, ofJson &json, string prefix){
    if(group == nullptr){
        return;
    }
    
    
    auto n = group->getNumControls();
    try
    {
        
        
//        string basePath = ofFilePath::join(prefix, group->getName());
//        string name = group->getName() + "_Gui_group_tooltip";
//
//        if(json.contains(name)){
//            json.at(name).get_to(tooltipsMap[group]);
//        }else{
//            json[name] = "";
//        }
        getSetTooltip(group, json, true);
        
        for(size_t i = 0; i < n; i++){
            ofxBaseGui* c = group->getControl(i);
            if(c){
                
                ofxGuiGroup * g = dynamic_cast<ofxGuiGroup*>(c);
                if(g){
//                    cout << prefix << " group : " << c->getName() << endl;
                    getGuiControlPaths(g,  json[c->getName()], prefix + "    ");
                }else{
//                    cout << prefix << c->getName() << endl;
                    getSetTooltip(c, json["group"]);
//                    name = c->getName();
//                    if(json.contains(name)){
//                        json.at(name).get_to(tooltipsMap[c]);
//                    }else{
//                        json[name] = "";
//                    }
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

//---------------------------------------------------------------------
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
    
//    headerRect.set(b.x, b.y , b.width, defaultHeight);
    
    auto n = group->getNumControls();
    
    for(size_t i = 0; i < n; i++){
        ofxBaseGui* c = group->getControl(i);
        if(c){
//            cout << c->getShape() << "\n";
            if(c->getShape().inside(x, y)){
                ofxGuiGroup * g = dynamic_cast<ofxGuiGroup*>(c);
                if(g){
                    return findOverGui(g, x, y);
                }
                return c;
            }
        }
    }
    return nullptr;//static_cast<ofxBaseGui*>(group);
}

//---------------------------------------------------------------------
void ofxGuiTooltip::registerGui(ofxGuiGroup* group, const string& stringsFilepath, const string& jsonSubPath){
//    if(!ofFile::doesFileExist(stringsFilepath)){
//        ofLogNotice("ofxGuiTooltip::registerGui") << "File path does not exist. Cant load";
//        return;
        
//    }
    bool bFound = false;
    for(auto g : guis){
        if(g && g == group){
            bFound = true;
            break;
//            ofLogNotice("ofxGuiTooltip::registerGui") << "Gui already registered.";
//            return;
        }
    }
    if(!bFound){
        guis.push_back(group);
    }
    ofJson json;
    if(ofFile::doesFileExist(stringsFilepath)){
        json = ofLoadJson(stringsFilepath);
    }
    
    getGuiControlPaths(group, (jsonSubPath.empty())?json:json[jsonSubPath]);
//    if(!jsonSubPath.empty()){
        ofSavePrettyJson(stringsFilepath, json);
//    }
    enable();
}

//---------------------------------------------------------------------
void ofxGuiTooltip::unregisterGui(ofxGuiGroup* group){
    ofRemove(guis, [group](ofxGuiGroup*g){
        return g == group;
    });
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
        float x = ofGetMouseX();
        float y = ofGetMouseY();
//        for(auto g: tooltipsMap){
//            if(g.first && g.first->getShape().inside(x, y)){
//                ofDrawBitmapStringHighlight(g.second, x, y - 20, ofColor::lightYellow, ofColor::black);
//            }
//        }
        if(overGui){
            ofDrawBitmapStringHighlight(currentTooltip, x, y - 20, ofColor::lightYellow, ofColor::black);
        }
        
    }
}

//---------------------------------------------------------------------
void ofxGuiTooltip::registerMouse(){
    if(!bMouseRegistered){
        bMouseRegistered = true;
        listeners.push(ofEvents().mouseMoved.newListener(this, &ofxGuiTooltip::mouseOver, -100));
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
    currentTooltip = "";
    for(auto g : guis){
        if(g){
            auto c = findOverGui(g, x,y);
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
}
//---------------------------------------------------------------------
void ofxGuiTooltip::disable(){
    bIsEnabled = false;
    unregisterMouse();
}

