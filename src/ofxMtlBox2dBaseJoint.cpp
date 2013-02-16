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
//  ofxMtlBox2dBaseJoint.cpp
//  ofxMtlBox2d
//
//  Created by Elie Zananiri on 2013-02-15.
//  Based on ofxBox2d by Todd Vanderlin: http://code.google.com/p/vanderlin/
//

#include "ofxMtlBox2d.h"

//------------------------------------------------
ofxMtlBox2dBaseJoint::ofxMtlBox2dBaseJoint()
{
    m_world = NULL;
    m_joint = NULL;
}

//------------------------------------------------
ofxMtlBox2dBaseJoint::~ofxMtlBox2dBaseJoint()
{
    if (m_joint) destroy();
}

//------------------------------------------------
b2Body * ofxMtlBox2dBaseJoint::getBodyA()
{
    if (m_joint)
        m_joint->GetBodyA();

    return NULL;
}

//------------------------------------------------
b2Body * ofxMtlBox2dBaseJoint::getBodyB()
{
    if (m_joint)
        m_joint->GetBodyB();

    return NULL;
}

//------------------------------------------------
const ofPoint ofxMtlBox2dBaseJoint::getAnchorA()
{
    return VEC2PT(m_joint->GetAnchorA());
}

//------------------------------------------------
const b2Vec2 ofxMtlBox2dBaseJoint::getAnchorAB2()
{
    return m_joint->GetAnchorA();
}

//------------------------------------------------
const ofPoint ofxMtlBox2dBaseJoint::getAnchorB()
{
    return VEC2PT(m_joint->GetAnchorB());
}

//------------------------------------------------
const b2Vec2 ofxMtlBox2dBaseJoint::getAnchorBB2()
{
    return m_joint->GetAnchorB();
}

//------------------------------------------------
void ofxMtlBox2dBaseJoint::destroy()
{
    if (!m_world) {
        ofLog(OF_LOG_WARNING, "ofxMtlBox2dDistanceJoint::destroy() Must have a valid b2World");
        return;
    }
    else if (!m_joint) {
        ofLog(OF_LOG_WARNING, "ofxMtlBox2dDistanceJoint::destroy() NULL joint");
        return;
    }

    m_world->DestroyJoint(m_joint);
    m_joint  = NULL;
}
