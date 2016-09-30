#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "ParticleController.h"
#include "cinder/params/Params.h"

using namespace ci;
using namespace ci::app;
using namespace std;


class FlockingTutorial030App : public App {
public:
    void setup() override;
    void update() override;
    void draw() override;
private:
    const int NUM_PARTICLES = 500;
    CameraPersp mCamera;
    vec3 mEye, mCenter, mUp;
    params::InterfaceGlRef mParams;
    quat mSceneRotation;
    float mCameraDistance, mZoneRadius, mThreshold;
    bool mCentralGravity, mFlattenTo2D, mDrawParticleTails;
    ParticleController mParticleController;
};

void FlockingTutorial030App::setup() {
    mZoneRadius = 65.0f;
    mThreshold = 0.65f;
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
    mParams = params::InterfaceGl::create("Flocking", vec2(225, 300));
    mParams->addParam("Scene Rotation", &mSceneRotation, "opened=1"); // the opened param opens the panel per default
    mParams->addSeparator();
    mParams->addParam("Eye Distance", &mCameraDistance, "min=50.0 max=1000.0 step=50.0 keyIncr=s keyDecr=w");
    mParams->addParam("Center Gravity", &mCentralGravity, "keyIncr=g");
    mParams->addParam("Flatten to 2D", &mFlattenTo2D, "keyIncr=f");
    mParams->addParam("Draw particle tails", &mDrawParticleTails, "keyIncr=p");
    mParams->addSeparator();
    mParams->addParam("Zone Radius", &mZoneRadius, "min=10.0 max=100.0, step=2.5 keyIncr=z keyDecr=Z");
    mParams->addParam("Threshold", &mThreshold, "min=0.025 max=1.0, step=0.025 keyIncr=t keyDecr=T");

    // PARTICLE CONTROLLER
    // -------------------
    mParticleController.addParticles(NUM_PARTICLES);
}

void FlockingTutorial030App::update() {
    // write frame rate into window title
    getWindow()->setTitle("fps: " + to_string(getAverageFps()));

    // update camera orientation
    mEye.z = mCameraDistance;
    mCamera.lookAt(mEye, mCenter, mUp);

    // update scene matrices
    gl::setMatrices(mCamera);
    gl::rotate(mSceneRotation);

    // update particles
    mParticleController.applyFlocking(mZoneRadius, mThreshold);
    if (mCentralGravity) {
        mParticleController.applyCenterPull(mCenter);
    }
    mParticleController.update(mFlattenTo2D);
}

void FlockingTutorial030App::draw() {
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
    gl::color(0.25f, 0.25f, 1.0f);
    gl::drawSolidCircle(vec2(), mZoneRadius * mThreshold);
    gl::color(Color(1.0f, 1.0f, 1.0f));
    gl::drawStrokedCircle(vec2(), 100.0f);
    gl::popModelMatrix();

    // draw the params interface
    mParams->draw();
}


CINDER_APP(
        FlockingTutorial030App,
        RendererGl(RendererGl::Options().msaa(16)),
        [&](App::Settings *settings){
            settings->setWindowSize(1280, 720);
            settings->setFrameRate(60.0f);
		}
)