#pragma once

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
    void addParticles(int amount, const vec2 &location);
    void removeParticles(int amount);
private:
    list<Particle> mParticles;
};