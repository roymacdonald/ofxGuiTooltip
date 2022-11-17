////
////  ofxGuiTooltipBase.hpp
////  LidarSlam2
////
////  Created by Roy Macdonald on 17-11-22.
////
//
#pragma once
#include "ofJson.h"
#include "ofxBaseGui.h"

class ofxGuiTooltipBase {
public:
    ///\brief set tooltips for this dropdown.
    ///If there is no tooltip data for any of the tooltip options, including nested dropdowns
    ///the json object will get populated with empty strings so it is easier to fill out.
    ///Make sure to save the json back to disk in order to save this auto generated json.
    ///\param json the json object containing the tooltip data
    virtual void setupTooltip(ofJson & json);
    
    
    
    ///\brief set tooltips for this dropdown.
    ///If there is no tooltip data for any of the tooltip options, including nested dropdowns
    ///the json file will get populated with empty strings so it is easier to fill out.
    ///If any option does not have a tooltip it will be saved into the same json file in a non destructive way (what ever was there is there will be kept.
    ///\param json file path to the json file
    void setupTooltip(const std::string& jsonFilePath);
    
    ///\ reset all tooltips. This works recursively with any nested dropdown
    virtual void resetTooltips();
    
    void removeTooltip();
    
    ///\brief Enable tooltips. This works recursively with any nested dropdown
    virtual void enableTooltip();
    ///\brief Disable tooltips. This works recursively with any nested dropdown
    virtual void disableTooltip();
    
    
    ///\brief check if tooltips are enabled
    ///\return boolean. true when the tooltip is enabled, false otherwise
    bool isTooltipEnabled();
    
    ///\brief Draw the tooltips.
    ///This needs to be called independently and after the dropdown and gui are drawn,
    ///otherwise the tooltips might get occluded by the gui.
    virtual void drawTooltip();
    
    ///\brief sets the text to be drawn when displaying the tooltip
    void setTooltipText(const std::string& text);
    
protected:
    
    
    ofxBaseGui * guiElement  = nullptr;
    
    virtual bool isOver() = 0;
    
    bool bTooltipsEnabled = false;
    
    std::string tooltipText;
    ofRectangle tooltipRect;

};
