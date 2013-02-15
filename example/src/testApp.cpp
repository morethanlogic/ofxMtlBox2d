#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    ofSeedRandom();
    ofSetFrameRate(30);
    ofEnableAlphaBlending();
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetBackgroundAuto(false);
	ofSetLogLevel(OF_LOG_NOTICE);
    
    // init the physics world
    world = physics.getWorld();
    physics.enableMouseJoints();
    physics.setGravityB2(b2Vec2(0, 9.8));
    physics.createBounds(0, 0, ofGetWidth(), ofGetHeight());
    
    bDebug = true;
}

//--------------------------------------------------------------
void testApp::update()
{
    physics.update();
}

//--------------------------------------------------------------
void testApp::draw()
{
    ofBackground(0, 0, 0);

    physics.debug();
    
    if (bDebug) {
        ofSetColor(255, 255, 255);
        ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate(), 2) +
                           "\nBODIES: " + ofToString((int)bodies.size()) +
                           "\nLEFT-CLICK TO ADD A CIRCLE, RIGHT-CLICK TO ADD A BOX", 10, 20);        
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
	switch (key) {
        case 'd':
            bDebug = !bDebug;
            break;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
    if (button == 0) {
        // build a new circle
        ofxMtlBox2dCircle *circle = new ofxMtlBox2dCircle();
        circle->setPhysics(10, .2f, .5f);
        circle->setup(world, x, y, ofRandom(20, 50), ofRandom(0, 359));
        bodies.push_back(circle);
    }
    else {
        // build a new box
        ofxMtlBox2dBox *box = new ofxMtlBox2dBox();
        box->setPhysics(10, .2f, .5f);
        box->setup(world, x, y, ofRandom(20, 50), ofRandom(20, 50), ofRandom(0, 359));
        bodies.push_back(box);
    } 
}

//--------------------------------------------------------------
void testApp::mouseReleased()
{

}
