#include "Particle.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"

Particle::Particle(vec2 location) {
    mLocation = location;
    mDirection = Rand::randVec2();
    mVelocity = Rand::randFloat(5.0f);
    mRadius = 5.0f;
}

void Particle::update() {
    mLocation += mDirection * mVelocity;
}

void Particle::draw() {
    gl::drawSolidCircle(mLocation, mRadius);
}





