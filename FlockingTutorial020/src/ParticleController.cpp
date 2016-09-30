#include <cinder/Rand.h>
#include "ParticleController.h"


ParticleController::ParticleController() {
}

void ParticleController::update(const bool &flattenTo2D) {
    for (list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p) {
        p->update(flattenTo2D);
    }
}

void ParticleController::draw(const bool &drawTails) {
    for (list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p) {
        p->draw();
    }

    gl::begin(GL_LINES);
    if (drawTails) {
        for (list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p) {
            p->drawTail();
        }
    }
    gl::end();
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

void ParticleController::applySeparation(float particleZoneRadiusSqrd) {
    for (list<Particle>::iterator p1 = mParticles.begin(); p1 != mParticles.end(); ++p1) {
        list<Particle>::iterator p2 = p1;
        for (++p2; p2 != mParticles.end(); ++p2) {
            vec3 dir = p1->getPosition() - p2->getPosition();
            float distSqrd = glm::length2(dir);
            if (distSqrd <= particleZoneRadiusSqrd) { // SEPARATION
                float F = (particleZoneRadiusSqrd / distSqrd - 1.0f) * 0.01f;
                dir = glm::normalize(dir);
                dir *= F;
                p1->applyForce(dir); // add force
                p2->applyForce(dir * -1.0f); // substract force
            }
        }
    }
}

void ParticleController::pullToCenter(const vec3 &center) {
    for (list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p) {
        p->pullToCenter(center);
    }
}















