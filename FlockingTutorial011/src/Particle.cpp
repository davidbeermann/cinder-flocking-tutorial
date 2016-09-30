#include <cinder/Perlin.h>
#include "Particle.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"

Particle::Particle(vec3 location, vec3 velocity) {
    mLocation = location;
    mVelocity = velocity;
    mRadius = 2.0f;
    mMass = mRadius * mRadius * 0.005f;
    mDecay = Rand::randFloat(0.95f, 0.99f);
}

void Particle::update() {
    // apply acceleration to velocity
    mVelocity += mAcceleration;
    // move particle with velocity
    mLocation += mVelocity;
    // reset acceleration
    mAcceleration *= 0;
    // slow down velocity
//    mVelocity *= mDecay;
}

void Particle::draw() {
    float r = mRadius * agePercentageInverted();
    gl::drawSphere(mLocation, r, 16);
}

void Particle::pullToCenter(const vec3 &center) {
    vec3 dirToCenter = mLocation - center;
    float distToCenter = glm::length(dirToCenter);
    float maxDistance = 300.0f;
    if (distToCenter > maxDistance) {
        dirToCenter = glm::normalize(dirToCenter);
        float pullStrength = 0.0001f;
        mVelocity -= dirToCenter * ((distToCenter - maxDistance) * pullStrength);
    }
}

vec3 Particle::getLocation() {
    return mLocation;
}

float Particle::getMass() {
    return mMass;
}

float Particle::agePercentage() {
    return 0.0f; //mAge / (float) mLifespan;
}

float Particle::agePercentageInverted() {
    return 1.0f - agePercentage();
}

















