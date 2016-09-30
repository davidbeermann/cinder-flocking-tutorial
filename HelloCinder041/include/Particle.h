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
    bool isDead();
private:
    vec2 mLocation;
    float mRadius;
    int mAge;
    int mLifespan;
    bool mIsDead;
};
