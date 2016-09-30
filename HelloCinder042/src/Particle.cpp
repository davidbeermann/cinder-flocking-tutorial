#include "Particle.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"

Particle::Particle(vec2 location, vec2 velocity) {
    mLocation = location;
    mVelocity = velocity;
    mRadius = 5.0f;
    mAge = 0;
    mLifespan = Rand::randInt(50, 250);
    mIsDead = false;
    mDecay = Rand::randFloat(0.95f, 0.99f);
}

void Particle::update() {
    // move particle
    mLocation += mVelocity;
    // slow down velocity
    mVelocity *= mDecay;
    // evaluate when particle dies.
    mIsDead = (++mAge > mLifespan);
}

void Particle::draw() {
    float r = mRadius * (1.0f - mAge / (float) mLifespan);
    gl::drawSolidCircle(mLocation, r);
}

bool Particle::isDead() {
    return mIsDead;
}







