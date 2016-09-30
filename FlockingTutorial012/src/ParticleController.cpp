#include <cinder/Rand.h>
#include "ParticleController.h"


ParticleController::ParticleController() {
}

void ParticleController::update() {
    for (list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p) {
        p->update();
    }
}

void ParticleController::draw() {
    for (list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p) {
        p->draw();
    }
}

void ParticleController::addParticles(int amount) {
    int i = 0;
    while (i < amount) {
        vec3 l = Rand::randVec3() * 50.0f;
        vec3 v = Rand::randVec3() * 5.0f;
        mParticles.push_back(Particle(l, v));
        ++i;
    }
}

void ParticleController::pullToCenter(const vec3 &center) {
    for (list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p) {
        p->pullToCenter(center);
    }
}













