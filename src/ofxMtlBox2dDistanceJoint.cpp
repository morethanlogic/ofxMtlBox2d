//
//  ofxMtlBox2dDistanceJoint.cpp
//  Caterpillar
//
//  Created by Elie Zananiri on 2013-02-15.
//
//

#include "ofxMtlBox2dDistanceJoint.h"

//------------------------------------------------
ofxMtlBox2dDistanceJoint::ofxMtlBox2dDistanceJoint()
{
    mWorld = NULL;
    mJoint = NULL;
}

//------------------------------------------------
ofxMtlBox2dDistanceJoint::~ofxMtlBox2dDistanceJoint()
{
    if (mJoint) destroy();
}

//------------------------------------------------
bool ofxMtlBox2dDistanceJoint::setWorld(b2World* world)
{
    if (!world) {
		ofLog(OF_LOG_WARNING, "ofxMtlBox2dDistanceJoint::setWorld() Must have a valid b2World");
		return false;
	}

    mWorld = world;
    return true;
}

//------------------------------------------------
void ofxMtlBox2dDistanceJoint::setPhysics(float frequency, float damping)
{
    _jd.frequencyHz  = frequency;
    _jd.dampingRatio = damping;
}

//------------------------------------------------
void ofxMtlBox2dDistanceJoint::setup(b2World *world, b2Body *body1, b2Body *body2)
{
    if (!setWorld(world)) return;

    // create a joint and add it to the world
    b2Vec2 anchor1 = body1->GetWorldCenter();
    b2Vec2 anchor2 = body2->GetWorldCenter();

    _jd.Initialize(body1, body2, anchor1, anchor2);

    mJoint = (b2DistanceJoint *)mWorld->CreateJoint(&_jd);
}

//------------------------------------------------
void ofxMtlBox2dDistanceJoint::setLength(float length)
{
    if (mJoint)
        mJoint->SetLength(PIX2M(length));
}

//------------------------------------------------
void ofxMtlBox2dDistanceJoint::setLengthB2(float length)
{
    if (mJoint)
        mJoint->SetLength(length);
}

//------------------------------------------------
float ofxMtlBox2dDistanceJoint::getLength()
{
    return M2PIX(mJoint->GetLength());
}

//------------------------------------------------
float ofxMtlBox2dDistanceJoint::getLengthB2()
{
    return mJoint->GetLength();
}

//------------------------------------------------
void ofxMtlBox2dDistanceJoint::destroy()
{
    if (!mWorld) {
        ofLog(OF_LOG_WARNING, "ofxMtlBox2dDistanceJoint::destroy() Must have a valid b2World");
        return;
    }
    else if (!mJoint) {
        ofLog(OF_LOG_WARNING, "ofxMtlBox2dDistanceJoint::destroy() NULL joint");
        return;
    }

    mWorld->DestroyJoint(mJoint);
    mJoint  = NULL;
}
