#pragma once

// main cinder header file
#include "cinder/app/App.h"
// access main cinder namespaces
using namespace ci;
using namespace ci::app;
using namespace std;

class Particle {
public:
    Particle(vec3 location, vec3 velocity);
    void update();
    void draw();
    void pullToCenter(const vec3 &center);
    vec3 getLocation();
    float getMass();
private:
    vec3 mLocation, mVelocity, mAcceleration;
    float mMass, mRadius, mDecay;
    float agePercentage();
    float agePercentageInverted();
};
