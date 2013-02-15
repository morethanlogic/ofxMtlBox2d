//
//  ofxMtlBox2dPolygon.cpp
//  Caterpillar
//
//  Created by Elie Zananiri on 2013-02-15.
//
//

#include "ofxMtlBox2dPolygon.h"

//------------------------------------------------
ofxMtlBox2dPolygon::ofxMtlBox2dPolygon()
{

}

//------------------------------------------------
ofxMtlBox2dPolygon::~ofxMtlBox2dPolygon()
{

}

//------------------------------------------------
void ofxMtlBox2dPolygon::setup(b2World *world, vector<ofPoint>& points, bool bStatic)
{
    if (!setWorld(world)) return;

    // create a body and add it to the world
    _bd.type = bStatic? b2_staticBody : b2_dynamicBody;
    
    mBody = mWorld->CreateBody(&_bd);

    // add the shape
//    vector<b2Vec2> verts;
//    for (int i = 0; i < points.size(); i++) {
//        verts.push_back(PT2VEC(points[i]));
//    }
//
//    b2PolygonShape polygon;
//    polygon.Set(&verts[0], verts.size());
//
//    _fd.shape = &polygon;
//    mFixture = mBody->CreateFixture(&_fd);

    for (int i = 1; i < points.size(); i++) {
        b2PolygonShape polygon;
        b2Vec2 a = PT2VEC(points[i - 1]);
        b2Vec2 b = PT2VEC(points[i]);
        polygon.SetAsEdge(a, b);
        
        _fd.shape		= &polygon;
        mBody->CreateFixture(&_fd);
    }
}
