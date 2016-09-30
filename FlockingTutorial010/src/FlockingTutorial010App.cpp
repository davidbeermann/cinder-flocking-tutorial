#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/params/Params.h"

using namespace ci;
using namespace ci::app;
using namespace std;


class FlockingTutorial010App : public App {
public:
    void setup() override;
    void update() override;
    void draw() override;
private:
    CameraPersp mCamera;
    vec3 mEye, mCenter, mUp;
    params::InterfaceGlRef mParams;
    quat mSceneRotation;
    float mCameraDistance;
    gl::BatchRef mCube;
};

void FlockingTutorial010App::setup() {
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

    // TEST OBJECT SETUP
    // -----------------
    // create basic cube mesh
    auto mesh = geom::Cube().size(vec3(40.0f));
    // define constant color for mesh
    auto color = geom::Constant(geom::COLOR, Color(CM_HSV, 0,1,1));
    // create shader
    auto lambert = gl::ShaderDef().lambert().color();
    gl::GlslProgRef shader = gl::getStockShader(lambert);
    // bake mesh and shader into batch object
    // concatenating mesh and color combines the properties
    mCube = gl::Batch::create(mesh >> color, shader);
}

void FlockingTutorial010App::update() {
    // write frame rate into window title
    getWindow()->setTitle("fps: " + to_string(getAverageFps()));

    // update camera orientation
    mEye.z = mCameraDistance;
    mCamera.lookAt(mEye, mCenter, mUp);

    // update scene matrices
    gl::setMatrices(mCamera);
    gl::rotate(mSceneRotation);
}

void FlockingTutorial010App::draw() {
    // clear window background
    gl::clear();
    // enable depth
    gl::enableDepthRead();
    gl::enableDepthWrite();
    // draw test object
    gl::pushModelMatrix();
    gl::translate(vec3(0.0f));
    mCube->draw();
    gl::popModelMatrix();
    // draw the params interface
    mParams->draw();
}


CINDER_APP(
        FlockingTutorial010App,
        RendererGl(RendererGl::Options().msaa(16)),
        [&](App::Settings *settings) {
            settings->setWindowSize(1280, 720);
            settings->setFrameRate(60.0f);
        }
)