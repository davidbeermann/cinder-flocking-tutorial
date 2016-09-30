#pragma once

// main cinder header file
#include "cinder/app/App.h"
// access main cinder namespaces
using namespace ci;
using namespace ci::app;
using namespace std;

class Particle {
public:
    Particle(vec2 location, vec2 velocity);
    void update(const Perlin &perlin, const vec2 &mouseLocation);
    void draw();
    bool isDead();
private:
    vec2 mLocation;
    vec2 mVelocity;
    float mRadius;
    int mAge;
    int mLifespan;
    bool mIsDead;
    float mDecay;
    float agePercentage();
    float agePercentageInverted();
};
