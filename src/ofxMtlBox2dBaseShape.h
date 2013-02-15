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
 *  ofxMtlBox2dBaseShape.h
 *  ofxMtlBox2d
 *
 *  Created by Elie Zananiri on 10-10-06.
 *  Based on ofxBox2d by Todd Vanderlin: http://code.google.com/p/vanderlin/
 */

#pragma once

#include "ofxMtlBox2d.h"

//========================================================================
class ofxMtlBox2dBaseShape
{    
    public:
                        ofxMtlBox2dBaseShape();
        virtual         ~ofxMtlBox2dBaseShape();
    
        bool            setWorld(b2World *world);
        void            setPhysics(float mass, float friction, float bounce);
        void            setFilterData(const b2Filter data);
    
        void            setFixedRotation(bool bFixed);
        bool            isFixedRotation();
    
        void            setAngularDamping(float damping);
        float           getAngularDamping();
        void            setLinearDamping(float damping);
        float           getLinearDamping();
        
        void            setPosition(const ofPoint& pos);
        void            setPositionB2(const b2Vec2& pos);
        const ofPoint   getPosition();
        const b2Vec2&   getPositionB2();
    
        float           getRotation();
        const float     getRotationB2();
    
        void            setLinearVelocity(const ofPoint& vel);
        void            setLinearVelocityB2(const b2Vec2& vel);
        const b2Vec2    getLinearVelocity();
        const b2Vec2    getLinearVelocityB2();
    
        void            setAngularVelocity(float vel);
        float           getAngularVelocity();
    
        void            applyForce(const ofPoint& force, const ofPoint& point);
        void            applyForceB2(const b2Vec2& force, const b2Vec2& point);
        void            applyLinearImpulse(const ofPoint& impulse, const ofPoint& point);
        void            applyLinearImpulseB2(const b2Vec2& impulse, const b2Vec2& point);
        void            applyAngularImpulse(float impulse);
        
        void            destroy();
    
        virtual void    update() {}
        virtual void    draw() {}
    
        b2World*        mWorld;
        b2Body*         mBody;
        b2Fixture*      mFixture;
    
    protected:
        // cached structs
        b2BodyDef       _bd;
        b2FixtureDef    _fd;
        b2Vec2          _pos;
        float           _ang;
};
