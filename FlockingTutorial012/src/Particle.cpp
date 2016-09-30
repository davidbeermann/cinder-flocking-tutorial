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

    // bake mesh and shader into batch reference
    auto mesh = geom::Sphere().radius(mRadius).subdivisions(16);
    auto color = geom::Constant(geom::COLOR, Color(CM_HSV, 0.0f, 1.0f, 1.0f));
    auto lambert = gl::ShaderDef().lambert().color();
    auto shader = gl::getStockShader(lambert);
    mSphere = gl::Batch::create(mesh, shader);
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
    // create scoped model matrix which resets automatically at the end of this block.
    gl::ScopedModelMatrix scpModelMatrix;
    gl::translate(mLocation);
    // hue is not working yet
    // lmap() is equivalent to Processing's map() function
    float hue = lmap(atan2(mLocation.y, mLocation.x), -(float) M_PI, (float) M_PI, 0.0f, 1.0f);
    gl::color(CM_HSV, hue, 1.0f, 1.0f);
    mSphere->draw();
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

















