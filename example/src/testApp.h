#pragma once

#include "ofMain.h"
#include "ofxMtlBox2d.h"
#include "ofxMtlBox2dCircle.h"
#include "ofxMtlBox2dBox.h"

//========================================================================
class testApp : public ofBaseApp {
	
	public:
		void                setup();
		void                update();
		void                draw();
		
		void                keyPressed(int key);
		void                keyReleased(int key);
		void                mouseMoved(int x, int y);
		void                mouseDragged(int x, int y, int button);
		void                mousePressed(int x, int y, int button);
		void                mouseReleased();
    
        ofxMtlBox2d         physics;
        b2World*            world;
        vector<ofxMtlBox2dBaseShape*> bodies;
    
        bool                debug;
        bool                info;
		
};
