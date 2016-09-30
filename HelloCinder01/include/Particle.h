#pragma once

// main cinder header file
#include "cinder/app/App.h"
// access main cinder namespaces
using namespace ci;
using namespace ci::app;
using namespace std;

class Particle {
public:
    Particle(vec2 location);
    void update();
    void draw();
private:
    vec2 mLocation;
    vec2 mDirection;
    float mVelocity;
    float mRadius;
};
