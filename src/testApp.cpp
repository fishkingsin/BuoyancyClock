/**
 *  testApp.cpp
 *
 *  Created by Marek Bereza on 09/01/2012.
 */

#include "testApp.h"
int currentMinute = 0;
int currentSecond = 0;
float decay = 0.9995;
float dvi = 1;
//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
    ofBackground(255);
    ofEnableAlphaBlending();
    buffer0 = new float [ofGetWidth()];
    buffer1 = new float [ofGetWidth()];
    buffer2 = new float [ofGetWidth()];
    
    
    length = ofGetWidth()/dvi;
    
    for (int i = 0 ; i<= length; i++) {
        
        buffer.push_back(ofPoint(i*dvi,ofGetHeight()*0.5));
        color.push_back(ofFloatColor(0.5,0.5,0.5,0.5));
        
        buffer0[i] = 0;
        buffer1[i] = 0;
        buffer2[i] = 0;
    }
    
    
    buffer.push_back(ofPoint(length*dvi,ofGetHeight()));
    color.push_back(ofFloatColor(0.5,0.5,0.5,0.5));
    
    buffer.push_back(ofPoint(0,ofGetHeight()));
    color.push_back(ofFloatColor(0.5,0.5,0.5,0.5));
    
    font.loadFont("HelveticaBold.ttf", 248);
    int step = ofGetWidth()/6.0;
    object[0].setupData("0", &font, buffer2, step);
    object[1].setupData("0", &font, buffer2, step*2);
    
    object[2].setupData("0", &font, buffer2, step*4);
    object[3].setupData("0", &font, buffer2, step*5);
    
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    
    //find
    for (int x=1; x < length-1; x++){
        buffer0[x] = (buffer1[x-1]+ buffer1[x+1]) / 2.0;
        buffer0[x] = buffer0[x] * 2.0 - buffer2[x];
        buffer0[x] *= decay;
    }
    //swap
    for (int i = 0 ; i< length; i++) {
        
        
        buffer2[i] -= (buffer2[i] - buffer1[i]) * decay;
        buffer1[i] -= (buffer1[i] - buffer0[i]) * decay;
        buffer[i].y = buffer2[i]+ofGetHeight()*0.5;
    }
    
    
    for (int i = 0 ; i< 4; i++) {
        if(object[i].update())
        {
            makeRipple(object[i].x , 0 );
        }
    }
    
    if(currentSecond!=ofGetSeconds())
    {
        string timestamp = ofGetTimestampString("%H%M");
        for(int i = 0 ; i  <4 ; i++)
        {
            if(object[i].str[0]!=timestamp[i])
            {
                string targetString = " ";
                targetString[0] = timestamp[i];
                object[i].reset(  targetString );
            }
        }

        currentSecond = ofGetSeconds();
//        makeRipple(ofRandom(ofGetWidth()),0);
    }
    
}
void testApp::makeRipple(int x , int y )
{
    float distance = 200;
    for (int _x=1 ; _x<length-1; _x++){
        float d = abs(x-_x);
        if (d < distance){
            buffer1[(int)ofMap(_x,0,ofGetWidth(),0,length)] -= pow(((distance - d)/distance),2) * -5;
        }
    }
}
//--------------------------------------------------------------
void testApp::draw(){
    
    for (int i = 0 ; i< 4; i++) {
        object[i].draw();
    }
    
    ofSetColor(125, 125, 125,125);
    ofBeginShape();
	for (int i = 0; i < buffer.size(); i++){
        
		ofVertex(buffer[i].x,buffer[i].y);
	}
	ofEndShape();
    
}
