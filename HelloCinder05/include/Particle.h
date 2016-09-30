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
    void applyForce(const vec2 &force);
    bool isDead();
    vec2 getLocation();
    float getMass();
private:
    vec2 mLocation;
    vec2 mVelocity;
    vec2 mAcceleration;
    float mMass;
    float mRadius;
    int mAge;
    int mLifespan;
    bool mIsDead;
    float mDecay;
    float agePercentage();
    float agePercentageInverted();
};
