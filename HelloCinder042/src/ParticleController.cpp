#include <cinder/Rand.h>
#include "ParticleController.h"


ParticleController::ParticleController() {
}

void ParticleController::update() {
    // the for loop has no iteration statement!!!
    // this is because we only iterate in the list after a particle update.
    // if a particle is erased from the list we do not increment the list pointer.
    // this is a standard practice for using the STL list class.
    for (list<Particle>::iterator p = mParticles.begin(); p != mParticles.end();) {
        if (p->isDead()) {
            p = mParticles.erase(p);
        } else {
            p->update();
            ++p;
        }
    }
}

void ParticleController::draw() {
    for (list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p) {
        p->draw();
    }
}

void ParticleController::addParticles(int amount, const vec2 &location, const vec2 &velocity) {
    int i = 0;
    while (i < amount) {
        vec2 l = location + Rand::randVec2() * 10.0f;
        vec2 v = velocity * 0.25f + Rand::randVec2() * Rand::randFloat(1.0f, 3.0f);
        mParticles.push_back(Particle(l, v));
        ++i;
    }
}

void ParticleController::removeParticles(int amount) {
}









