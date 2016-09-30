#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/params/Params.h"
#include "ParticleController.h"

using namespace ci;
using namespace ci::app;
using namespace std;


class FlockingTutorial011App : public App {
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
	float mCameraDistance;
    ParticleController mParticleController;
};

void FlockingTutorial011App::setup() {
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
	mParams = params::InterfaceGl::create("Flocking", vec2(225, 200));
	mParams->addParam("Scene Rotation", &mSceneRotation);
	mParams->addParam("Eye Distance", &mCameraDistance, "min=50.0 max=1000.0 step=50.0 keyIncr=s keyDecr=w");

    // PARTICLE CONTROLLER
    // -------------------
    mParticleController.addParticles(NUM_PARTICLES);
}

void FlockingTutorial011App::update() {
	// write frame rate into window title
	getWindow()->setTitle("fps: " + to_string(getAverageFps()));

	// update camera orientation
	mEye.z = mCameraDistance;
	mCamera.lookAt(mEye, mCenter, mUp);

	// update scene matrices
	gl::setMatrices(mCamera);
	gl::rotate(mSceneRotation);

    // update particles
    mParticleController.pullToCenter(mCenter);
    mParticleController.update();
}

void FlockingTutorial011App::draw() {
	// clear window background
	gl::clear();
	// enable depth
	gl::enableDepthRead();
	gl::enableDepthWrite();
	// draw particlesr
    mParticleController.draw();
	// draw the params interface
	mParams->draw();
}


CINDER_APP(
        FlockingTutorial011App,
        RendererGl(RendererGl::Options().msaa(16)),
        [&](App::Settings *settings){
            settings->setWindowSize(1280, 720);
            settings->setFrameRate(60.0f);
		}
)