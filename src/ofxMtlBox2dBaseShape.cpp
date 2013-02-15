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
 *  ofxMtlBox2dBaseShape.cpp
 *  ofxMtlBox2d
 *
 *  Created by Elie Zananiri on 10-10-06.
 *  Based on ofxBox2d by Todd Vanderlin: http://code.google.com/p/vanderlin/
 */

#include "ofxMtlBox2dBaseShape.h"

//------------------------------------------------
ofxMtlBox2dBaseShape::ofxMtlBox2dBaseShape()
{
    mWorld = NULL;
    mBody  = NULL;
    
    _bd.allowSleep = true;
}		

//------------------------------------------------ 
ofxMtlBox2dBaseShape::~ofxMtlBox2dBaseShape()
{
    if (mBody) destroy();
}

//------------------------------------------------ 
bool ofxMtlBox2dBaseShape::setWorld(b2World* world)
{
    if (!world) {
		ofLog(OF_LOG_WARNING, "ofxMtlBox2dBaseShape::setWorld() Must have a valid b2World");
		return false;
	}
    
    mWorld = world;
    return true;
}

//------------------------------------------------ 
void ofxMtlBox2dBaseShape::setPhysics(float mass, float friction, float bounce)
{
    _fd.density     = mass;
    _fd.friction    = friction;
    _fd.restitution = bounce;
}

//------------------------------------------------ 
void ofxMtlBox2dBaseShape::setFilterData(const b2Filter data)
{
    if (mFixture)
        mFixture->SetFilterData(data);
}

//------------------------------------------------ 
void ofxMtlBox2dBaseShape::setFixedRotation(bool bFixed)
{
    if (mBody)
        mBody->SetFixedRotation(bFixed);
    else
        _bd.fixedRotation = bFixed;
}

//------------------------------------------------ 
bool ofxMtlBox2dBaseShape::isFixedRotation()
{
    if (mBody)
        return mBody->IsFixedRotation();
    
    return _bd.fixedRotation;
}

//------------------------------------------------ 
void ofxMtlBox2dBaseShape::setAngularDamping(float damping)
{
    if (mBody)
        mBody->SetAngularDamping(damping);
    else
        _bd.angularDamping = damping;
}

//------------------------------------------------
float ofxMtlBox2dBaseShape::getAngularDamping()
{
    return mBody->GetAngularDamping();
}

//------------------------------------------------ 
void ofxMtlBox2dBaseShape::setLinearDamping(float damping)
{
    if (mBody)
        mBody->SetLinearDamping(damping);
    else
        _bd.linearDamping = damping;
}

//------------------------------------------------
float ofxMtlBox2dBaseShape::getLinearDamping()
{
    return mBody->GetLinearDamping();
}

//------------------------------------------------ 
void ofxMtlBox2dBaseShape::setPosition(const ofPoint& pos)
{
    mBody->SetTransform(PT2VEC(pos), 0);
}

//------------------------------------------------ 
void ofxMtlBox2dBaseShape::setPositionB2(const b2Vec2& pos)
{
    mBody->SetTransform(pos, 0);
}
                
//------------------------------------------------ 
const ofPoint ofxMtlBox2dBaseShape::getPosition()
{
    return VEC2PT(mBody->GetPosition());
}

//------------------------------------------------
const b2Vec2& ofxMtlBox2dBaseShape::getPositionB2()
{
    return mBody->GetPosition();
}

//------------------------------------------------
float ofxMtlBox2dBaseShape::getRotation()
{
    return RAD2DEG(mBody->GetAngle());
}

//------------------------------------------------
const float ofxMtlBox2dBaseShape::getRotationB2()
{
    return mBody->GetAngle();
}

//------------------------------------------------ 
void ofxMtlBox2dBaseShape::setLinearVelocity(const ofPoint& vel)
{
    mBody->SetLinearVelocity(PT2VEC(vel));
}

//------------------------------------------------ 
void ofxMtlBox2dBaseShape::setLinearVelocityB2(const b2Vec2& vel)
{
    mBody->SetLinearVelocity(vel);
}

//------------------------------------------------ 
const b2Vec2 ofxMtlBox2dBaseShape::getLinearVelocity()
{
    return M2PIX(mBody->GetLinearVelocity());
}

//------------------------------------------------ 
const b2Vec2 ofxMtlBox2dBaseShape::getLinearVelocityB2()
{
    return mBody->GetLinearVelocity();
}

//------------------------------------------------ 
void ofxMtlBox2dBaseShape::setAngularVelocity(float vel)
{
    mBody->SetAngularVelocity(vel);
}

//------------------------------------------------ 
float ofxMtlBox2dBaseShape::getAngularVelocity()
{
    return mBody->GetAngularVelocity();
}

//------------------------------------------------
void ofxMtlBox2dBaseShape::applyForce(const ofPoint& force, const ofPoint& point)
{
    if (mBody)
        mBody->ApplyForce(PT2VEC(force), PT2VEC(point));
}

//------------------------------------------------
void ofxMtlBox2dBaseShape::applyForceB2(const b2Vec2& force, const b2Vec2& point)
{
    if (mBody)
        mBody->ApplyForce(force, point);
}

//------------------------------------------------
void ofxMtlBox2dBaseShape::applyLinearImpulse(const ofPoint& impulse, const ofPoint& point)
{
    if (mBody)
        mBody->ApplyLinearImpulse(PT2VEC(impulse), PT2VEC(point));
}

//------------------------------------------------
void ofxMtlBox2dBaseShape::applyLinearImpulseB2(const b2Vec2& impulse, const b2Vec2& point)
{
    if (mBody)
        mBody->ApplyLinearImpulse(impulse, point);
}

//------------------------------------------------
void ofxMtlBox2dBaseShape::applyAngularImpulse(float impulse)
{
    if (mBody)
        mBody->ApplyAngularImpulse(impulse);
}

//------------------------------------------------
void ofxMtlBox2dBaseShape::destroy()
{
    if (!mWorld) {
        ofLog(OF_LOG_WARNING, "ofxMtlBox2dBaseShape::destroy() Must have a valid b2World");
        return;
    }
    else if (!mBody) {
        ofLog(OF_LOG_WARNING, "ofxMtlBox2dBaseShape::destroy() NULL body");
        return;
    }
    
    mWorld->DestroyBody(mBody);
    mBody  = NULL;
}

