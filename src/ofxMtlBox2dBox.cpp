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
 *  ofxMtlBox2dBox.cpp
 *  ofxMtlBox2d
 *
 *  Created by Elie Zananiri on 10-10-06.
 *  Based on ofxBox2d by Todd Vanderlin: http://code.google.com/p/vanderlin/
 */

#include "ofxMtlBox2dBox.h"

//------------------------------------------------
ofxMtlBox2dBox::ofxMtlBox2dBox()
{
    _dir   = new GLfloat[4];
    _verts = new GLfloat[4 * 2];
}

//------------------------------------------------
ofxMtlBox2dBox::~ofxMtlBox2dBox()
{
    delete [] _dir;
    delete [] _verts;
}

//------------------------------------------------
void ofxMtlBox2dBox::setup(b2World *world, float x, float y, float width, float height, float angle, bool bStatic)
{
    if (!setWorld(world)) return;
    
    // create a body and add it to the world
    _bd.type = bStatic? b2_staticBody : b2_dynamicBody;
    _bd.position.Set(PIX2M(x), PIX2M(y));
    _bd.angle = DEG2RAD(angle);
    
    mBody = mWorld->CreateBody(&_bd);
    
    // add collision shapes to that body
    _width  = width;
    _height = height;
    b2PolygonShape box;
    box.SetAsBox(PIX2M(_width/2), PIX2M(_height/2));
    
    _fd.shape = &box;
    mFixture = mBody->CreateFixture(&_fd);
}
