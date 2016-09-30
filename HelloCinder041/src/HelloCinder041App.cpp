#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "ParticleController.h"

using namespace ci;
using namespace ci::app;
using namespace std;


class HelloCinder041App : public App {
public:
    void setup() override;
    void update() override;
    void draw() override;
    void mouseDown(MouseEvent event) override;
    void mouseUp(MouseEvent event) override;
    void mouseMove(MouseEvent event) override;
    void mouseDrag(MouseEvent event) override;
private:
    ParticleController mParticleController;
    bool mMousePressed;
    vec2 mMouseLocation;
};

void HelloCinder041App::setup() {
    mMousePressed = false;
}

void HelloCinder041App::update() {
    getWindow()->setTitle("fps: " + to_string(getAverageFps()));
    if (mMousePressed) {
        mParticleController.addParticles(5, mMouseLocation);
    }
    mParticleController.update();
}

void HelloCinder041App::draw() {
    gl::clear();
    mParticleController.draw();
}

void HelloCinder041App::mouseDown(MouseEvent event) {
    mMousePressed = true;
}

void HelloCinder041App::mouseUp(MouseEvent event) {
    mMousePressed = false;
}

void HelloCinder041App::mouseMove(MouseEvent event) {
    mMouseLocation = event.getPos();
}

void HelloCinder041App::mouseDrag(MouseEvent event) {
    mouseMove(event);
}


CINDER_APP(
        HelloCinder041App,
        RendererGl(RendererGl::Options().msaa(16)),
        [&](App::Settings *settings) {
            settings->setWindowSize(800, 600);
            settings->setFrameRate(60.0f);
        }
)