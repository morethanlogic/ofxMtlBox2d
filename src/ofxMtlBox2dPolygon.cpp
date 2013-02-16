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
//  ofxMtlBox2dPolygon.cpp
//  ofxMtlBox2d
//
//  Created by Elie Zananiri on 2013-02-15.
//  Based on ofxBox2d by Todd Vanderlin: http://code.google.com/p/vanderlin/
//

#include "ofxMtlBox2dPolygon.h"
#include "ofxMtlBox2d.h"

//------------------------------------------------
ofxMtlBox2dPolygon::ofxMtlBox2dPolygon()
{

}

//------------------------------------------------
ofxMtlBox2dPolygon::~ofxMtlBox2dPolygon()
{

}

//------------------------------------------------
void ofxMtlBox2dPolygon::setup(ofxMtlBox2dWorld *world, vector<ofPoint>& points, bool bStatic)
{
    vector<b2Vec2> pts;
    for (int i = 0; i < points.size(); i++)
        pts.push_back(PT2VEC(points[i]));

    setupB2(world->m_world, pts, bStatic);
}

//------------------------------------------------
void ofxMtlBox2dPolygon::setupB2(b2World *world, vector<b2Vec2>& points, bool bStatic)
{
    m_world = world;

    // create a body and add it to the world
    _bd.type = bStatic? b2_staticBody : b2_dynamicBody;
    
    m_body = m_world->CreateBody(&_bd);

    // add the shape
//    vector<b2Vec2> verts;
//    for (int i = 0; i < points.size(); i++) {
//        verts.push_back(points[i]);
//    }
//
//    b2PolygonShape polygon;
//    polygon.Set(&verts[0], verts.size());
//
//    _fd.shape = &polygon;
//    mFixture = mBody->CreateFixture(&_fd);

    for (int i = 1; i < points.size(); i++) {
        b2PolygonShape polygon;
        b2Vec2 a = points[i - 1];
        b2Vec2 b = points[i];
        polygon.SetAsEdge(a, b);
        
        _fd.shape = &polygon;
        m_body->CreateFixture(&_fd);
    }
}
