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
//  ofxMtlBox2dRevoluteJoint.cpp
//  Caterpillar
//
//  Created by Elie Zananiri on 2013-02-15.
//
//

#include "ofxMtlBox2dRevoluteJoint.h"

//------------------------------------------------
ofxMtlBox2dRevoluteJoint::ofxMtlBox2dRevoluteJoint()
{

}

//------------------------------------------------
ofxMtlBox2dRevoluteJoint::~ofxMtlBox2dRevoluteJoint()
{

}

//------------------------------------------------
void ofxMtlBox2dRevoluteJoint::setup(b2World *world, b2Body *bodyA, b2Body *bodyB, const b2Vec2& anchor)
{
    if (!setWorld(world)) return;

    // create a joint and add it to the world
    _jd.Initialize(bodyA, bodyB, b2Vec2(PIX2M(anchor.x), PIX2M(anchor.y)));

    mJoint = mWorld->CreateJoint(&_jd);
}

//------------------------------------------------
void ofxMtlBox2dRevoluteJoint::setLimitEnabled(bool flag)
{
    if (mJoint)
        ((b2RevoluteJoint *)mJoint)->EnableLimit(flag);
    else
        _jd.enableLimit = flag;
}

//------------------------------------------------
bool ofxMtlBox2dRevoluteJoint::isLimitEnabled()
{
    if (mJoint)
        return ((b2RevoluteJoint *)mJoint)->IsLimitEnabled();
    else
        return _jd.enableLimit;
}

//------------------------------------------------
void ofxMtlBox2dRevoluteJoint::setLimits(float lowerAngle, float upperAngle)
{
    if (mJoint)
        ((b2RevoluteJoint *)mJoint)->SetLimits(DEG2RAD(lowerAngle), DEG2RAD(upperAngle));
    else {
        _jd.lowerAngle = DEG2RAD(lowerAngle);
        _jd.upperAngle = DEG2RAD(upperAngle);
    }
}

//------------------------------------------------
void ofxMtlBox2dRevoluteJoint::setLimitsB2(float lowerAngle, float upperAngle)
{
    if (mJoint)
        ((b2RevoluteJoint *)mJoint)->SetLimits(lowerAngle, upperAngle);
    else {
        _jd.lowerAngle = lowerAngle;
        _jd.upperAngle = upperAngle;
    }
}

//------------------------------------------------
float ofxMtlBox2dRevoluteJoint::getLowerLimit()
{
    if (mJoint)
        return RAD2DEG(((b2RevoluteJoint *)mJoint)->GetLowerLimit());
    else
        return RAD2DEG(_jd.lowerAngle);
}

//------------------------------------------------
float ofxMtlBox2dRevoluteJoint::getLowerLimitB2()
{
    if (mJoint)
        return ((b2RevoluteJoint *)mJoint)->GetLowerLimit();
    else
        return _jd.lowerAngle;
}

//------------------------------------------------
float ofxMtlBox2dRevoluteJoint::getUpperLimit()
{
    if (mJoint)
        return RAD2DEG(((b2RevoluteJoint *)mJoint)->GetUpperLimit());
    else
        return RAD2DEG(_jd.upperAngle);
}

//------------------------------------------------
float ofxMtlBox2dRevoluteJoint::getUpperLimitB2()
{
    if (mJoint)
        return ((b2RevoluteJoint *)mJoint)->GetUpperLimit();
    else
        return _jd.upperAngle;
}
