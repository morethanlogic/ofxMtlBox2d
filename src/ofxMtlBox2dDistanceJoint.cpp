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

//
//  ofxMtlBox2dDistanceJoint.cpp
//  ofxMtlBox2d
//
//  Created by Elie Zananiri on 2013-02-15.
//  Based on ofxBox2d by Todd Vanderlin: http://code.google.com/p/vanderlin/
//

#include "ofxMtlBox2dDistanceJoint.h"
#include "ofxMtlBox2d.h"

//------------------------------------------------
ofxMtlBox2dDistanceJoint::ofxMtlBox2dDistanceJoint()
{

}

//------------------------------------------------
ofxMtlBox2dDistanceJoint::~ofxMtlBox2dDistanceJoint()
{

}

//------------------------------------------------
void ofxMtlBox2dDistanceJoint::setPhysics(float frequency, float damping)
{
    _jd.frequencyHz  = frequency;
    _jd.dampingRatio = damping;
}

//------------------------------------------------
void ofxMtlBox2dDistanceJoint::setup(ofxMtlBox2dWorld *world, ofxMtlBox2dBaseShape *bodyA, ofxMtlBox2dBaseShape *bodyB)
{
    setupB2(world->m_world, bodyA->m_body, bodyB->m_body);
}

//------------------------------------------------
void ofxMtlBox2dDistanceJoint::setup(ofxMtlBox2dWorld *world, ofxMtlBox2dBaseShape *bodyA, ofxMtlBox2dBaseShape *bodyB, const ofPoint& anchorA, const ofPoint& anchorB)
{
    setupB2(world->m_world, bodyA->m_body, bodyB->m_body, PT2VEC(anchorA), PT2VEC(anchorB));
}

//------------------------------------------------
void ofxMtlBox2dDistanceJoint::setupB2(b2World *world, b2Body *bodyA, b2Body *bodyB)
{
    setupB2(world, bodyA, bodyB, bodyA->GetWorldCenter(), bodyB->GetWorldCenter());
}

//------------------------------------------------
void ofxMtlBox2dDistanceJoint::setupB2(b2World *world, b2Body *bodyA, b2Body *bodyB, const b2Vec2& anchorA, const b2Vec2& anchorB)
{
    m_world = world;
    
    // create a joint and add it to the world
    _jd.Initialize(bodyA, bodyB, anchorA, anchorB);

    m_joint = m_world->CreateJoint(&_jd);
}

//------------------------------------------------
void ofxMtlBox2dDistanceJoint::setLength(float length)
{
    if (m_joint)
        ((b2DistanceJoint *)m_joint)->SetLength(PIX2M(length));
}

//------------------------------------------------
void ofxMtlBox2dDistanceJoint::setLengthB2(float length)
{
    if (m_joint)
        ((b2DistanceJoint *)m_joint)->SetLength(length);
}

//------------------------------------------------
float ofxMtlBox2dDistanceJoint::getLength()
{
    return M2PIX(((b2DistanceJoint *)m_joint)->GetLength());
}

//------------------------------------------------
float ofxMtlBox2dDistanceJoint::getLengthB2()
{
    return ((b2DistanceJoint *)m_joint)->GetLength();
}
