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
//  ofxMtlBox2dWorld.cpp
//  ofxMtlBox2d
//
//  Created by Elie Zananiri on 10-10-06.
//  Based on ofxBox2d by Todd Vanderlin: http://code.google.com/p/vanderlin/
//

#include "ofxMtlBox2dWorld.h"
#include "ofxMtlBox2d.h"

//--------------------------------------------------------------
ofxMtlBox2dWorld::ofxMtlBox2dWorld()
{
    // create the world
    m_world = new b2World(b2Vec2(0, 0), true);
    m_world->SetDebugDraw(&m_debugDraw);

    m_bounds = NULL;
    m_mouseJoint = NULL;
}

//--------------------------------------------------------------
ofxMtlBox2dWorld::~ofxMtlBox2dWorld()
{
    delete m_world;
    m_world = NULL;
}

//--------------------------------------------------------------
void ofxMtlBox2dWorld::createBounds(float x, float y, float width, float height)
{
    if (!m_world) {
        ofLog(OF_LOG_WARNING, "ofxMtlBox2dWorld::createBounds() Must have a valid b2World");
		return;
    }

    if (m_bounds) {
        // delete the previous bounds
        m_world->DestroyBody(m_bounds);
    }
    
    b2BodyDef bd;
    m_bounds = m_world->CreateBody(&bd);
    
    b2PolygonShape shape;
    
    // top
    shape.SetAsEdge(b2Vec2(0, 0), b2Vec2(PIX2M(width), 0));
    m_bounds->CreateFixture(&shape, 0.0f);
    
    // bottom
    shape.SetAsEdge(b2Vec2(0, PIX2M(height)), b2Vec2(PIX2M(width), PIX2M(height)));
    m_bounds->CreateFixture(&shape, 0.0f);
    
    // left
    shape.SetAsEdge(b2Vec2(0, 0), b2Vec2(0, PIX2M(height)));
    m_bounds->CreateFixture(&shape, 0.0f);
    
    // right
    shape.SetAsEdge(b2Vec2(PIX2M(width), 0), b2Vec2(PIX2M(width), PIX2M(height)));
    m_bounds->CreateFixture(&shape, 0.0f);
}

//--------------------------------------------------------------
void ofxMtlBox2dWorld::update(float fps)
{
	m_world->Step(1 / fps, VEL_ITERATIONS, POS_ITERATIONS);
}

//--------------------------------------------------------------
void ofxMtlBox2dWorld::setGravity(const ofPoint& gravity)
{
    m_world->SetGravity(PT2VEC(gravity));
}

//--------------------------------------------------------------
void ofxMtlBox2dWorld::setGravityB2(const b2Vec2& gravity)
{
    m_world->SetGravity(gravity);
}

//--------------------------------------------------------------
ofPoint ofxMtlBox2dWorld::getGravity() const
{
    return VEC2PT(m_world->GetGravity());
}

//--------------------------------------------------------------
b2Vec2 ofxMtlBox2dWorld::getGravityB2() const
{
    return m_world->GetGravity();
}

//--------------------------------------------------------------
void ofxMtlBox2dWorld::debug()
{
    m_world->DrawDebugData();
}

//--------------------------------------------------------------
int ofxMtlBox2dWorld::getBodyCount()
{
    return m_world->GetBodyCount();
}

//--------------------------------------------------------------
int ofxMtlBox2dWorld::getJointCount()
{
    return m_world->GetJointCount();
}

//--------------------------------------------------------------
void ofxMtlBox2dWorld::enableMouseJoints()
{
#ifdef TARGET_OF_IPHONE
	ofAddListener(ofEvents.touchDown,  this, &ofxMtlBox2dWorld::onPress);
	ofAddListener(ofEvents.touchMoved, this, &ofxMtlBox2dWorld::onDrag);
	ofAddListener(ofEvents.touchUp,    this, &ofxMtlBox2dWorld::onRelease);
#else
	ofAddListener(ofEvents().mousePressed,  this, &ofxMtlBox2dWorld::onPress);
	ofAddListener(ofEvents().mouseDragged,  this, &ofxMtlBox2dWorld::onDrag);
	ofAddListener(ofEvents().mouseReleased, this, &ofxMtlBox2dWorld::onRelease);
#endif
}

//--------------------------------------------------------------
void ofxMtlBox2dWorld::disableMouseJoints()
{
#ifdef TARGET_OF_IPHONE
	ofRemoveListener(ofEvents.touchDown,  this, &ofxMtlBox2dWorld::onPress);
	ofRemoveListener(ofEvents.touchMoved, this, &ofxMtlBox2dWorld::onDrag);
	ofRemoveListener(ofEvents.touchUp,    this, &ofxMtlBox2dWorld::onRelease);
#else
	ofRemoveListener(ofEvents().mousePressed,  this, &ofxMtlBox2dWorld::onPress);
	ofRemoveListener(ofEvents().mouseDragged,  this, &ofxMtlBox2dWorld::onDrag);
	ofRemoveListener(ofEvents().mouseReleased, this, &ofxMtlBox2dWorld::onRelease);
#endif
}

//--------------------------------------------------------------
#ifdef TARGET_OF_IPHONE
void ofxMtlBox2dWorld::onPress(ofTouchEventArgs &args)
#else
void ofxMtlBox2dWorld::onPress(ofMouseEventArgs &args)
#endif
{
    if (m_mouseJoint) return;
    
    b2Vec2 mousePt = PIX2M(b2Vec2(args.x, args.y));
    
	// make a small box
	b2AABB aabb;
	b2Vec2 d;
	d.Set(0.001f, 0.001f);
	aabb.lowerBound = mousePt - d;
	aabb.upperBound = mousePt + d;
    
	// query the world for overlapping shapes
	ofxMtlBox2dHitTestCallback callback(mousePt);
	m_world->QueryAABB(&callback, aabb);
    
	if (callback.fixture) {
		b2Body* hitBody = callback.fixture->GetBody();
		b2MouseJointDef md;
		md.bodyA = m_bounds;
		md.bodyB = hitBody;
		md.target = mousePt;
		md.maxForce = 1000.0f * hitBody->GetMass();
		m_mouseJoint = (b2MouseJoint *)m_world->CreateJoint(&md);
		hitBody->SetAwake(true);
	}   
}
    
//--------------------------------------------------------------
#ifdef TARGET_OF_IPHONE
void ofxMtlBox2dWorld::onDrag(ofTouchEventArgs &args)
#else
void ofxMtlBox2dWorld::onDrag(ofMouseEventArgs &args)
#endif
{
    if (m_mouseJoint) {
        b2Vec2 mousePt = PIX2M(b2Vec2(args.x, args.y));
		m_mouseJoint->SetTarget(mousePt);
	}
}
    
//--------------------------------------------------------------
#ifdef TARGET_OF_IPHONE
void ofxMtlBox2dWorld::onRelease(ofTouchEventArgs &args)
#else
void ofxMtlBox2dWorld::onRelease(ofMouseEventArgs &args)
#endif
{
    if (m_mouseJoint) {
		m_world->DestroyJoint(m_mouseJoint);
		m_mouseJoint = NULL;
	}
}
