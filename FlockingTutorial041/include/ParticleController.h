#pragma once

#include <cinder/Perlin.h>
#include "cinder/app/App.h"
#include "Particle.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ParticleController {
public:
    ParticleController();
    void update(const bool &flattenTo2D);
    void draw(const bool &drawTails);
    void addParticles(int amount);
    void applyFlocking(float zoneRadius, float lowerThreshold, float higherThreshold, float attractStrength, float repelStrength, float alignmentStrength);
    void applyCenterPull(const vec3 &center);
private:
    list<Particle> mParticles;
    float mMaxDistance, mMaxDistanceSquared, mCenterPullStrength;
};