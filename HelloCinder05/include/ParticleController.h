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
    void update(const Perlin &perlin, const vec2 &mouseLocation);
    void draw();
    void addParticles(int amount, const vec2 &location, const vec2 &velocity);
    void removeParticles(int amount);
    void repulseParticles();
private:
    list<Particle> mParticles;
};