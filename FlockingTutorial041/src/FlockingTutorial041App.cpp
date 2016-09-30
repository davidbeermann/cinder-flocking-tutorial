#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "ParticleController.h"
#include "cinder/params/Params.h"

using namespace ci;
using namespace ci::app;
using namespace ci::params;
using namespace std;


class FlockingTutorial041App : public App {
public:
    void setup() override;
    void update() override;
    void draw() override;
private:
    const int NUM_PARTICLES = 1000;
    CameraPersp mCamera;
    vec3 mEye, mCenter, mUp;
    InterfaceGlRef mParams;
    quat mSceneRotation;
    float mCameraDistance, mZoneRadius;
    float mLowerThreshold, mHigherThreshold;
    float mAttractStrength, mRepelStrength, mAlignStrength;
    bool mCentralGravity, mFlattenTo2D, mDrawParticleTails;
    ParticleController mParticleController;
};

void FlockingTutorial041App::setup() {
    mZoneRadius = 80.0f;
    mLowerThreshold = 0.4f;
    mHigherThreshold = 0.75f;
    mAttractStrength = 0.005f;
    mRepelStrength = 0.01f;
    mAlignStrength = 0.01f;

    mCentralGravity = true;
    mFlattenTo2D = false;
    mDrawParticleTails = true;

    // CAMERA SETUP
    // ------------
    // set initial distance to camera
    mCameraDistance = 500.0f;
    // setup camera orientation vectors
    mEye = vec3(0.0f, 0.0f, mCameraDistance);
    mCenter = vec3(0.0f, 0.0f, 0.0f);
    mUp = vec3(0.0f, 1.0f, 0.0f);
    // setup the camera frustum
    mCamera.setPerspective(60.0f, getWindowAspectRatio(), 5.0f, 3000.0f);

    // PARAMS SETUP
    // ------------
    // calling the InterfceGI constructor directly is deprecated.
    // use static member function create() instead.
    mParams = InterfaceGl::create("Flocking", vec2(250, 350));
    mParams->addParam("Scene Rotation", &mSceneRotation, "opened=1"); // the opened param opens the panel per default
    mParams->addSeparator();
    mParams->addParam("Eye Distance", &mCameraDistance, "min=50.0 max=1000.0 step=50.0 keyIncr=s keyDecr=w");
    mParams->addParam("Center Gravity", &mCentralGravity, "keyIncr=g");
    mParams->addParam("Flatten to 2D", &mFlattenTo2D, "keyIncr=f");
    mParams->addParam("Draw particle tails", &mDrawParticleTails, "keyIncr=t");
    mParams->addSeparator();
    mParams->addParam("Zone Radius", &mZoneRadius, "min=10.0 max=100.0, step=2.5 keyIncr=z keyDecr=Z");
    mParams->addParam("Lower Threshold", &mLowerThreshold, "min=0.025 max=1.0, step=0.025 keyIncr=l keyDecr=L");
    mParams->addParam("Higher Threshold", &mHigherThreshold, "min=0.025 max=1.0, step=0.025 keyIncr=h keyDecr=H");
    mParams->addSeparator();
    mParams->addParam("Attract Strength", &mAttractStrength, "min=0.001 max=0.1 step=0.001 keyIncr=a keyDecr=A");
    mParams->addParam("Repel Strength", &mRepelStrength, "min=0.001 max=0.1 step=0.001 keyIncr=r keyDecr=R");
    mParams->addParam("Orient Strength", &mAlignStrength, "min=0.001 max=0.1 step=0.001 keyIncr=o keyDecr=O");

    // PARTICLE CONTROLLER
    // -------------------
    mParticleController.addParticles(NUM_PARTICLES);
}

void FlockingTutorial041App::update() {
    // write frame rate into window title
    getWindow()->setTitle("fps: " + to_string(getAverageFps()));

    // update camera orientation
    mEye.z = mCameraDistance;
    mCamera.lookAt(mEye, mCenter, mUp);

    // update scene matrices
    gl::setMatrices(mCamera);
    gl::rotate(mSceneRotation);

    // update particles
    mParticleController.applyFlocking(mZoneRadius, mLowerThreshold, mHigherThreshold, mAttractStrength, mRepelStrength, mAlignStrength);
    if (mCentralGravity) {
        mParticleController.applyCenterPull(mCenter);
    }
    mParticleController.update(mFlattenTo2D);
}

void FlockingTutorial041App::draw() {
    // clear window background
    gl::clear();

    // draw particles
    gl::enableDepthRead();
    gl::enableDepthWrite();
    mParticleController.draw(mDrawParticleTails);

    // draw zone radius graphic
    gl::disableDepthRead();
    gl::disableDepthWrite();
    gl::setMatricesWindow(getWindowSize());
    gl::pushModelMatrix();
    gl::translate(vec2(117.0f, getWindowHeight() - 117.0f));
    gl::color(1.0f, 0.25f, 0.25f);
    gl::drawSolidCircle(vec2(), mZoneRadius);
    gl::color(0.25f, 1.0f, 0.25f);
    gl::drawSolidCircle(vec2(), mZoneRadius * mHigherThreshold);
    gl::color(0.25f, 0.25f, 1.0f);
    gl::drawSolidCircle(vec2(), mZoneRadius * mLowerThreshold);
    gl::color(Color(1.0f, 1.0f, 1.0f));
    gl::drawStrokedCircle(vec2(), 100.0f);
    gl::popModelMatrix();

    // draw the params interface
    mParams->draw();
}


CINDER_APP(
        FlockingTutorial041App,
        RendererGl(RendererGl::Options().msaa(16)),
        [&](App::Settings *settings){
            settings->setWindowSize(1280, 720);
            settings->setFrameRate(60.0f);
		}
)