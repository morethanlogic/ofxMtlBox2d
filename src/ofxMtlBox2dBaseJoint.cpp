/***********************************************************************
 *
 * Copyright (c) 2010-2013 Elie Zananiri, Hugues Bruyère
 * more than logic http://www.morethanlogic.com/
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of "more than logic" nor the names of its contributors
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ***********************************************************************/

/*
 *  ofxMtlBox2dBaseJoint.cpp
 *  ofxMtlBox2d
 *
 *  Created by Elie Zananiri on 2013-02-15.
 *  Based on ofxBox2d by Todd Vanderlin: http://code.google.com/p/vanderlin/
 */

#include "ofxMtlBox2dBaseJoint.h"

//------------------------------------------------
ofxMtlBox2dBaseJoint::ofxMtlBox2dBaseJoint()
{
    mWorld = NULL;
    mJoint = NULL;
}

//------------------------------------------------
ofxMtlBox2dBaseJoint::~ofxMtlBox2dBaseJoint()
{
    if (mJoint) destroy();
}

//------------------------------------------------
bool ofxMtlBox2dBaseJoint::setWorld(b2World* world)
{
    if (!world) {
		ofLog(OF_LOG_WARNING, "ofxMtlBox2dBaseJoint::setWorld() Must have a valid b2World");
		return false;
	}

    mWorld = world;
    return true;
}

//------------------------------------------------
b2Body * ofxMtlBox2dBaseJoint::getBodyA()
{
    if (mJoint)
        mJoint->GetBodyA();

    return NULL;
}

//------------------------------------------------
b2Body * ofxMtlBox2dBaseJoint::getBodyB()
{
    if (mJoint)
        mJoint->GetBodyB();

    return NULL;
}

//------------------------------------------------
const ofPoint ofxMtlBox2dBaseJoint::getAnchorA()
{
    return VEC2PT(mJoint->GetAnchorA());
}

//------------------------------------------------
const b2Vec2 ofxMtlBox2dBaseJoint::getAnchorAB2()
{
    return mJoint->GetAnchorA();
}

//------------------------------------------------
const ofPoint ofxMtlBox2dBaseJoint::getAnchorB()
{
    return VEC2PT(mJoint->GetAnchorB());
}

//------------------------------------------------
const b2Vec2 ofxMtlBox2dBaseJoint::getAnchorBB2()
{
    return mJoint->GetAnchorB();
}

//------------------------------------------------
void ofxMtlBox2dBaseJoint::destroy()
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
