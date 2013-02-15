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
 *  ofxMtlBox2dCircle.cpp
 *  ofxMtlBox2d
 *
 *  Created by Elie Zananiri on 10-10-06.
 *  Based on ofxBox2d by Todd Vanderlin: http://code.google.com/p/vanderlin/
 */

#include "ofxMtlBox2dCircle.h"

//------------------------------------------------
ofxMtlBox2dCircle::ofxMtlBox2dCircle() : ofxMtlBox2dBaseShape()
{
    _dir = new GLfloat[4];
}

//------------------------------------------------
ofxMtlBox2dCircle::~ofxMtlBox2dCircle()
{
    delete [] _dir;
}

//------------------------------------------------
void ofxMtlBox2dCircle::setup(b2World *world, float x, float y, float radius, float angle, bool bStatic)
{
    if (!setWorld(world)) return;
    
    // create a body and add it to the world
    _bd.type = bStatic? b2_staticBody : b2_dynamicBody;
    _bd.position.Set(PIX2M(x), PIX2M(y));
    _bd.angle = DEG2RAD(angle);
    
    mBody = mWorld->CreateBody(&_bd);
    
    // add collision shapes to that body
    _radius = radius;
    b2CircleShape circle;
    circle.m_radius = PIX2M(_radius);

    _fd.shape = &circle;
    mFixture = mBody->CreateFixture(&_fd);
}

//------------------------------------------------
float ofxMtlBox2dCircle::getRadius()
{
    return _radius;
}

//------------------------------------------------
void ofxMtlBox2dCircle::setRadius(float radius) {
    // save the transform parameters
    _bd.position = getPositionB2();
    _bd.angle    = getRotationB2();
    
    // destroy the current body
    mWorld->DestroyBody(mBody);
    
    // create a body and add it to the world
    mBody = mWorld->CreateBody(&_bd);
    
    // add collision shapes to that body
    _radius = radius;
    b2CircleShape circle;
    circle.m_radius = PIX2M(_radius);
    
    _fd.shape = &circle;
    mFixture = mBody->CreateFixture(&_fd);
}

