#include <cinder/Rand.h>
#include "ParticleController.h"


ParticleController::ParticleController() {
}

void ParticleController::update(const Perlin &perlin, const vec2 &mouseLocation) {
    // the for loop has no iteration statement!!!
    // this is because we only iterate in the list after a particle update.
    // if a particle is erased from the list we do not increment the list pointer.
    // this is a standard practice for using the STL list class.
    for (list<Particle>::iterator p = mParticles.begin(); p != mParticles.end();) {
        if (p->isDead()) {
            p = mParticles.erase(p);
        } else {
            p->update(perlin, mouseLocation);
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

void ParticleController::repulseParticles() {
    for (list<Particle>::iterator p1 = mParticles.begin(); p1 != mParticles.end(); ++p1) {
        // copy pointer to current particle as starting point for inner loop.
        list<Particle>::iterator p2 = p1;
        for (++p2; p2 != mParticles.end(); ++p2) {
            vec2 dir = p1->getLocation() - p2->getLocation();
            float dirSqrd = glm::length2(dir);
            if (dirSqrd > 0.0f) {
                dir = glm::normalize(dir);
                // factor by which the particles should repel each other.
                float F = 1.0f / dirSqrd;
                // limiting the strength of the force
                vec2 force = dir * (F / p1->getMass() > 5.0f ? 5.0f : F / p1->getMass());
                p1->applyForce(force);
                force = dir * (F / p2->getMass() > 5.0f ? 5.0f : F / p2->getMass());
                p2->applyForce(force * -1.0f);
            }
        }
    }
}











