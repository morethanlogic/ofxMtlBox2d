#pragma once

#include "ofMain.h"
#include "ofxMtlBox2d.h"

//========================================================================
class testApp : public ofBaseApp
{
	public:
		void    setup();
		void    update();
		void    draw();
		
		void    keyPressed(int key);
		void    keyReleased(int key);
		void    mouseMoved(int x, int y);
		void    mouseDragged(int x, int y, int button);
		void    mousePressed(int x, int y, int button);
		void    mouseReleased();
    
        ofxMtlBox2dWorld* world;
        vector<ofxMtlBox2dBaseShape*> bodies;
    
        bool    bInfo;
};
