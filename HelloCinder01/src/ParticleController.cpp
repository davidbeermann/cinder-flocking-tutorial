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
        float x = Rand::randFloat(getWindowWidth());
        float y = Rand::randFloat(getWindowHeight());
        mParticles.push_back(Particle(vec2(x, y)));
        ++i;
    }
}

void ParticleController::removeParticles(int amount) {
}









