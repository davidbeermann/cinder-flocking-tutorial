#include "Particle.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"

Particle::Particle(vec2 location) {
    mLocation = location;
    mRadius = 5.0f;
    mAge = 0;
    mLifespan = Rand::randInt(50, 250);
    mIsDead = false;
}

void Particle::update() {
    // evaluate when particle dies.
    mIsDead = (++mAge > mLifespan);
    // simplified version of the lifespan check.
//    mAge++;
//    if(mAge > mLifespan){
//        mIsDead = true;
//    }
}

void Particle::draw() {
    float r = mRadius * (1.0f - mAge / (float) mLifespan);
    gl::drawSolidCircle(mLocation, r);
}

bool Particle::isDead() {
    return mIsDead;
}







