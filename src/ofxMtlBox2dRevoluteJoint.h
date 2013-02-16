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
//  ofxMtlBox2dRevoluteJoint.h
//  ofxMtlBox2d
//
//  Created by Elie Zananiri on 2013-02-15.
//
//

#pragma once

#include "ofxMtlBox2dBaseJoint.h"
#include "ofxMtlBox2dWorld.h"
#include "ofxMtlBox2dBaseShape.h"

//========================================================================
class ofxMtlBox2dRevoluteJoint : public ofxMtlBox2dBaseJoint
{
    public:
                ofxMtlBox2dRevoluteJoint();
                ~ofxMtlBox2dRevoluteJoint();

        void    setup(ofxMtlBox2dWorld *world, ofxMtlBox2dBaseShape *bodyA, ofxMtlBox2dBaseShape *bodyB, const ofPoint& anchor);
        void    setupB2(b2World *world, b2Body *bodyA, b2Body *bodyB, const b2Vec2& anchor);

        void    setLimitEnabled(bool flag);
        bool    isLimitEnabled();

        void    setLimits(float lowerAngle, float upperAngle);
        void    setLimitsB2(float lowerAngle, float upperAngle);
        float   getLowerLimit();
        float   getLowerLimitB2();
        float   getUpperLimit();
        float   getUpperLimitB2();

    protected:
        // cached structs
        b2RevoluteJointDef  _jd;
};
