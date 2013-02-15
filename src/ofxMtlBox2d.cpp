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
 *  ofxMtlBox2d.cpp
 *  ofxMtlBox2d
 *
 *  Created by Elie Zananiri on 10-10-06.
 *  Based on ofxBox2d by Todd Vanderlin: http://code.google.com/p/vanderlin/
 */

#include "ofxMtlBox2d.h"
#include "ofxMtlBox2dHitTestCallback.h"

//--------------------------------------------------------------
ofxMtlBox2d::ofxMtlBox2d()
{
    // create the world
    _world = new b2World(b2Vec2(0, 0), true);
    _world->SetDebugDraw(&_debugDraw);
}

//--------------------------------------------------------------
ofxMtlBox2d::~ofxMtlBox2d()
{
    delete _world;
    _world = NULL;
}

//--------------------------------------------------------------
void ofxMtlBox2d::createBounds(float x, float y, float width, float height)
{
    if (!_world) {
        ofLog(OF_LOG_WARNING, "ofxMtlBox2d::createBounds() Must have a valid b2World");
		return;
    }
    
    b2BodyDef bd;
    _bounds = _world->CreateBody(&bd);
    
    b2PolygonShape shape;
    
    // top
    shape.SetAsEdge(b2Vec2(0, 0), b2Vec2(PIX2M(width), 0));
    _bounds->CreateFixture(&shape, 0.0f);
    
    // bottom
    shape.SetAsEdge(b2Vec2(0, PIX2M(height)), b2Vec2(PIX2M(width), PIX2M(height)));
    _bounds->CreateFixture(&shape, 0.0f);
    
    // left
    shape.SetAsEdge(b2Vec2(0, 0), b2Vec2(0, PIX2M(height)));
    _bounds->CreateFixture(&shape, 0.0f);
    
    // right
    shape.SetAsEdge(b2Vec2(PIX2M(width), 0), b2Vec2(PIX2M(width), PIX2M(height)));
    _bounds->CreateFixture(&shape, 0.0f);
}

//--------------------------------------------------------------
void ofxMtlBox2d::update(float fps)
{
	_world->Step(1 / fps, VEL_ITERATIONS, POS_ITERATIONS);
}

//--------------------------------------------------------------
void ofxMtlBox2d::setGravity(const ofPoint& gravity)
{
    _world->SetGravity(PT2VEC(gravity));
}

//--------------------------------------------------------------
void ofxMtlBox2d::setGravityB2(const b2Vec2& _gravity)
{
    _world->SetGravity(_gravity);
}

//--------------------------------------------------------------
ofPoint ofxMtlBox2d::getGravity() const
{
    return VEC2PT(_world->GetGravity());
}

//--------------------------------------------------------------
b2Vec2 ofxMtlBox2d::getGravityB2() const
{
    return _world->GetGravity();
}

//--------------------------------------------------------------
void ofxMtlBox2d::debug()
{
    _world->DrawDebugData();
}

//--------------------------------------------------------------
b2World* ofxMtlBox2d::getWorld()
{
    return _world;
}

//--------------------------------------------------------------
b2Body* ofxMtlBox2d::getBounds()
{
    return _bounds;
}

//--------------------------------------------------------------
int ofxMtlBox2d::getBodyCount()
{
    return _world->GetBodyCount();
}

//--------------------------------------------------------------
int ofxMtlBox2d::getJointCount()
{
    return _world->GetJointCount();
}

//--------------------------------------------------------------
void ofxMtlBox2d::enableMouseJoints()
{
#ifdef TARGET_OF_IPHONE
	ofAddListener(ofEvents.touchDown,  this, &ofxMtlBox2d::onPress);
	ofAddListener(ofEvents.touchMoved, this, &ofxMtlBox2d::onDrag);
	ofAddListener(ofEvents.touchUp,    this, &ofxMtlBox2d::onRelease);
#else
	ofAddListener(ofEvents().mousePressed,  this, &ofxMtlBox2d::onPress);
	ofAddListener(ofEvents().mouseDragged,  this, &ofxMtlBox2d::onDrag);
	ofAddListener(ofEvents().mouseReleased, this, &ofxMtlBox2d::onRelease);
#endif
}

//--------------------------------------------------------------
void ofxMtlBox2d::disableMouseJoints()
{
#ifdef TARGET_OF_IPHONE
	ofRemoveListener(ofEvents.touchDown,  this, &ofxMtlBox2d::onPress);
	ofRemoveListener(ofEvents.touchMoved, this, &ofxMtlBox2d::onDrag);
	ofRemoveListener(ofEvents.touchUp,    this, &ofxMtlBox2d::onRelease);
#else
	ofRemoveListener(ofEvents().mousePressed,  this, &ofxMtlBox2d::onPress);
	ofRemoveListener(ofEvents().mouseDragged,  this, &ofxMtlBox2d::onDrag);
	ofRemoveListener(ofEvents().mouseReleased, this, &ofxMtlBox2d::onRelease);
#endif
}

//--------------------------------------------------------------
#ifdef TARGET_OF_IPHONE
void ofxMtlBox2d::onPress(ofTouchEventArgs &args)
#else
void ofxMtlBox2d::onPress(ofMouseEventArgs &args)
#endif
{
    if (_mouseJoint) return;
    
    b2Vec2 mousePt = PIX2M(b2Vec2(args.x, args.y));
    
	// make a small box
	b2AABB aabb;
	b2Vec2 d;
	d.Set(0.001f, 0.001f);
	aabb.lowerBound = mousePt - d;
	aabb.upperBound = mousePt + d;
    
	// query the world for overlapping shapes
	ofxMtlBox2dHitTestCallback callback(mousePt);
	_world->QueryAABB(&callback, aabb);
    
	if (callback.fixture) {
		b2Body* hitBody = callback.fixture->GetBody();
		b2MouseJointDef md;
		md.bodyA = _bounds;
		md.bodyB = hitBody;
		md.target = mousePt;
		md.maxForce = 1000.0f * hitBody->GetMass();
		_mouseJoint = (b2MouseJoint *)_world->CreateJoint(&md);
		hitBody->SetAwake(true);
	}   
}
    
//--------------------------------------------------------------
#ifdef TARGET_OF_IPHONE
void ofxMtlBox2d::onDrag(ofTouchEventArgs &args)
#else
void ofxMtlBox2d::onDrag(ofMouseEventArgs &args)
#endif
{
    if (_mouseJoint) {
        b2Vec2 mousePt = PIX2M(b2Vec2(args.x, args.y));
		_mouseJoint->SetTarget(mousePt);
	}
}
    
//--------------------------------------------------------------
#ifdef TARGET_OF_IPHONE
void ofxMtlBox2d::onRelease(ofTouchEventArgs &args)
#else
void ofxMtlBox2d::onRelease(ofMouseEventArgs &args)
#endif
{
    if (_mouseJoint) {
		_world->DestroyJoint(_mouseJoint);
		_mouseJoint = NULL;
	}
}
