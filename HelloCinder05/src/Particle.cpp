#include <cinder/Perlin.h>
#include "Particle.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"

Particle::Particle(vec2 location, vec2 velocity) {
    mLocation = location;
    mVelocity = velocity;
    mRadius = 5.0f;
    mMass = mRadius * mRadius * 0.005f;
    mAge = 0;
    mLifespan = Rand::randInt(50, 250);
    mIsDead = false;
    mDecay = Rand::randFloat(0.95f, 0.99f);
}

void Particle::update(const Perlin &perlin, const vec2 &mouseLocation) {
    // apply acceleration to velocity
    mVelocity += mAcceleration;
    // generate a noise float value based on a 3D vector.
    // the z-dimension is time-based in case the location is static the noise method will still return alternating values.
    // fBm() stands for 'fractional Brownian movement'.
    float noise = perlin.fBm(vec3(mouseLocation * 0.005f, getElapsedSeconds() * 0.1f));
    // the generated noise value lies within -1.0f and 1.0f, but mostly will be between -0.25f and 0.25f.
    // therefore the scale for the angle needs to be bigger than 2*M_PI (whole circle)
    // to get angles which do not tend in a certain direction.
    float angle = noise * 15.0f;
    // calculate velocity based on polar coordinates.
    vec2 noiseVector(cos(angle), sin(angle));
    // tone down perlin noise characteristic
    mVelocity += noiseVector * 0.2f * agePercentageInverted();
    // move particle with velocity
    mLocation += mVelocity;
    // reset acceleration
    mAcceleration *= 0;
    // slow down velocity
    mVelocity *= mDecay;
    // evaluate when particle dies.
    mIsDead = (++mAge > mLifespan);
}

void Particle::draw() {
    float r = mRadius * agePercentageInverted();
    gl::drawSolidCircle(mLocation, r);
}

void Particle::applyForce(const vec2 &force) {
    mAcceleration += force;
}

bool Particle::isDead() {
    return mIsDead;
}

vec2 Particle::getLocation() {
    return mLocation;
}

float Particle::getMass() {
    return mMass;
}

float Particle::agePercentage() {
    return mAge / (float) mLifespan;
}

float Particle::agePercentageInverted() {
    return 1.0f - agePercentage();
}

















