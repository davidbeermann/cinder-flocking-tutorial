#pragma once

// main cinder header file
#include "cinder/app/App.h"
// access main cinder namespaces
using namespace ci;
using namespace ci::app;
using namespace std;

class Particle {
public:
    Particle(vec3 position, vec3 velocity);
    void update(const bool &flattenTo2D);
    void draw();
    void drawTail();
    void applyForce(const vec3 &force);
    vec3 getPosition();
    vec3 getNormalizedVelocity();
private:
    vec3 mPosition, mVelocity, mAcceleration;
    vec3 mVelocityNormalized, mTailPosition;
    float mRadius, mDecay, mTailLength;
    float mMaxSpeed, mMaxSpeedSquared, mMinSpeed, mMinSpeedSquared;
    gl::BatchRef mSphere;
};
