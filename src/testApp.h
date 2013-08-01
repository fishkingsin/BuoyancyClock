/**     ___           ___           ___                         ___           ___     
 *     /__/\         /  /\         /  /\         _____         /  /\         /__/|    
 *    |  |::\       /  /::\       /  /::|       /  /::\       /  /::\       |  |:|    
 *    |  |:|:\     /  /:/\:\     /  /:/:|      /  /:/\:\     /  /:/\:\      |  |:|    
 *  __|__|:|\:\   /  /:/~/::\   /  /:/|:|__   /  /:/~/::\   /  /:/  \:\   __|__|:|    
 * /__/::::| \:\ /__/:/ /:/\:\ /__/:/ |:| /\ /__/:/ /:/\:| /__/:/ \__\:\ /__/::::\____
 * \  \:\~~\__\/ \  \:\/:/__\/ \__\/  |:|/:/ \  \:\/:/~/:/ \  \:\ /  /:/    ~\~~\::::/
 *  \  \:\        \  \::/          |  |:/:/   \  \::/ /:/   \  \:\  /:/      |~~|:|~~ 
 *   \  \:\        \  \:\          |  |::/     \  \:\/:/     \  \:\/:/       |  |:|   
 *    \  \:\        \  \:\         |  |:/       \  \::/       \  \::/        |  |:|   
 *     \__\/         \__\/         |__|/         \__\/         \__\/         |__|/   
 *
 *  Description: 
 *				 
 *  testApp.h, created by Marek Bereza on 09/01/2012.
 */

#pragma once
#include "ofMain.h"
#include "ofxAnimatableFloat.h"
#include "ofxAnimatableOfColor.h"

class MyObject
{
public:
    void setupData(string _str , ofTrueTypeFont* _font , float *_targetBuffer , int _x)
    {
        font = _font;
        str = _str;
        targetBuffer = _targetBuffer;
        
        y = 0;
        
        ofRectangle rect = font->getStringBoundingBox(str, 0, 0);
        height = rect.height*0.5;
        width = -rect.width*0.5;
        rotation  = ofRandom(-45 , 45);
        x = _x;
        sendtRipple = false;
    }
    void reset(string _str )
    {
        
        animationFloat.reset(-200);
        animationFloat.setCurve(LINEAR);
        animationFloat.setRepeatType(PLAY_ONCE);
        animationFloat.setDuration(5);
        animationFloat.animateToAfterDelay( ofGetHeight()*0.5 ,1);
        sendtRipple = false;
        
        
        animationColor.animateToAlpha(0);
        animationColor.setDuration(1);
        animationColor.setCurve(LINEAR);
        animationColor.setRepeatType(PLAY_ONCE);
        
        str = _str;
        
    }
    bool update()
    {
        
        float dt = 1.0f / 60;
        animationFloat.update( dt );
        animationColor.update( dt );
        if(animationColor.hasFinishedAnimating())
        {
            str2 = str;
            //            animationColor.animateToAlpha(255);
            //            animationColor.setDuration(0);
            
        }
        if(animationFloat.isAnimating())
        {
            animationColor.setAlphaOnly(255);
            y = animationFloat.val();
            sendtRipple = true;
            
        }
        else{
            if(sendtRipple)
            {
                animationColor.animateToAlpha(255);
                animationColor.setDuration(0);
                sendtRipple = false;
                return true;
            }
            y = targetBuffer[x]+ofGetHeight()*0.5;
        }
        return false;
        
    }
    void draw()
    {
        glPushMatrix();
        glTranslated(x, y, 0);
        glRotated(rotation, 0, 0, 1);
        ofPushStyle();
        ofEnableAlphaBlending();
        ofSetColor(animationColor.getCurrentColor());
        font->drawString(str2, width,height);
        ofPopStyle();
        glPopMatrix();
        
        
    }
    ofxAnimatableFloat animationFloat;
    ofxAnimatableOfColor animationColor;
    int x,y;
    ofTrueTypeFont*font;
    string str;
    string str2;
    float *targetBuffer;
    bool sendtRipple;
    int height,width;
    float rotation;
};

class testApp: public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

    float *buffer0;
    float *buffer1;
    float *buffer2;
    int length;
    
    vector<ofPoint>buffer;
    vector<ofFloatColor>color;
    void makeRipple(int x , int y);
    int y;
    
    MyObject object[4];
    ofTrueTypeFont font;

};
