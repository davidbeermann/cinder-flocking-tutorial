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
    void update();
    void draw();
    void addParticles(int amount);
    void pullToCenter(const vec3 &center);
private:
    list<Particle> mParticles;
};