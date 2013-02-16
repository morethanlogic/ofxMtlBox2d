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
//  ofxMtlBox2dWorld.h
//  ofxMtlBox2d
//
//  Created by Elie Zananiri on 10-10-06.
//  Based on ofxBox2d by Todd Vanderlin: http://code.google.com/p/vanderlin/
//

#pragma once

#include <Box2D.h>
#include "ofMain.h"

#include "ofxMtlBox2dDebugDraw.h"

//========================================================================
class ofxMtlBox2dWorld
{    
    public:
                ofxMtlBox2dWorld();
                ~ofxMtlBox2dWorld();
    
        void    createBounds(float x, float y, float width, float height);
    
        void    update(float fps = 30.0f);
        void    debug();
        
        void    setGravity(const ofPoint& gravity);
        void    setGravityB2(const b2Vec2& gravity);
        ofPoint getGravity() const;
        b2Vec2  getGravityB2() const;
        
        int		getBodyCount();
        int		getJointCount();
    
        void    enableMouseJoints();
        void    disableMouseJoints();
    
#ifdef TARGET_OF_IPHONE
        void    onPress(ofTouchEventArgs &args);
        void    onDrag(ofTouchEventArgs &args);
        void    onRelease(ofTouchEventArgs &args);
#else
        void    onPress(ofMouseEventArgs &args);
        void    onDrag(ofMouseEventArgs &args);
        void    onRelease(ofMouseEventArgs &args);
#endif
        
        b2World *               m_world;
        b2Body *                m_bounds;
        b2MouseJoint *          m_mouseJoint;
        ofxMtlBox2dDebugDraw    m_debugDraw;
};

