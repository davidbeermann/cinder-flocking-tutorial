#include <cinder/Perlin.h>
#include "Particle.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"

Particle::Particle(vec3 position, vec3 velocity) {
    mPosition = position;
    mVelocity = velocity;
    mAcceleration = vec3(0.0f);

    mVelocityNormalized = glm::normalize(velocity);
    mTailPosition = position;

    mMaxSpeed = Rand::randFloat(2.0f, 5.0f);
    mMaxSpeedSquared = mMaxSpeed * mMaxSpeed;
    mMinSpeed = Rand::randFloat(1.0f, 1.5f);
    mMinSpeedSquared = mMinSpeed * mMinSpeed;

    mRadius = 2.0f;
    mDecay = 0.99f;
    mTailLength = 10.0f;

    // bake mesh and shader into batch reference
    auto mesh = geom::Sphere().radius(mRadius).subdivisions(16);
    // color with zero saturation => white
    auto color = geom::Constant(geom::COLOR, Color(CM_HSV, 0.0f, 0.0f, 1.0f));
    auto lambert = gl::ShaderDef().lambert().color();
    auto shader = gl::getStockShader(lambert);
    mSphere = gl::Batch::create(mesh >> color, shader);
}

void Particle::update(const bool &flattenTo2D) {
    // strip z position from vectors
    if(flattenTo2D){
        mAcceleration.z = 0;
    }
    // update velocity
    mVelocity += mAcceleration;
    // store normalized velocity vector
    mVelocityNormalized = glm::normalize(mVelocity);
    // limit velocity's speed
    // take the squared length value for performance reasons!
    // the squared length does not take the square root in order to get the actual vector length.
    float v = glm::length2(mVelocity);
    if (v > mMaxSpeedSquared) {
        mVelocity = mVelocityNormalized * mMaxSpeed;
    } else if (v < mMinSpeedSquared) {
        mVelocity = mVelocityNormalized * mMinSpeed;
    }
    // update positions
    mPosition += mVelocity;
    mTailPosition = mPosition - mVelocityNormalized * mTailLength;
    if(flattenTo2D){
        mPosition.z = 0;
        mTailPosition.z = 0;
    }
    // slow down velocity
    mVelocity *= mDecay;
    // reset acceleration
    mAcceleration *= 0;
}

void Particle::draw() {
    gl::ScopedModelMatrix smm;
    gl::translate(mPosition);
    mSphere->draw();
}

void Particle::drawTail() {
    gl::color(1.0f, 1.0f, 1.0f);
    gl::vertex(mPosition);
    gl::color(1.0f, 0.0f, 0.0f);
    gl::vertex(mTailPosition);
}

void Particle::applyForce(const vec3 &force) {
    mAcceleration += force;
}

vec3 Particle::getPosition() {
    return mPosition;
}

vec3 Particle::getNormalizedVelocity() {
    return mVelocityNormalized;
}























