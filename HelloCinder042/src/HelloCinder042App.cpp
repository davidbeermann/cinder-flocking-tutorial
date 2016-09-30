#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "ParticleController.h"

using namespace ci;
using namespace ci::app;
using namespace std;


class HelloCinder042App : public App {
public:
    void setup() override;
    void update() override;
    void draw() override;
	void mouseDown(MouseEvent event) override;
	void mouseUp(MouseEvent event) override;
	void mouseMove(MouseEvent event) override;
	void mouseDrag(MouseEvent event) override;
private:
    const int PARTICLES_TO_SPAWN = 5;
	ParticleController mParticleController;
	bool mMousePressed;
	vec2 mMouseLocation;
	vec2 mMouseVelocity;
};

void HelloCinder042App::setup() {
    mMousePressed = false;
}

void HelloCinder042App::update() {
    getWindow()->setTitle("fps: " + to_string(getAverageFps()));
	if (mMousePressed) {
		mParticleController.addParticles(PARTICLES_TO_SPAWN, mMouseLocation, mMouseVelocity);
	}
	mParticleController.update();
}

void HelloCinder042App::draw() {
    gl::clear();
	mParticleController.draw();
}

void HelloCinder042App::mouseDown(MouseEvent event) {
	mMousePressed = true;
}

void HelloCinder042App::mouseUp(MouseEvent event) {
	mMousePressed = false;
}

void HelloCinder042App::mouseMove(MouseEvent event) {
	mMouseVelocity = (vec2(event.getPos()) - mMouseLocation);
	mMouseLocation = event.getPos();
}

void HelloCinder042App::mouseDrag(MouseEvent event) {
	mouseMove(event);
}


CINDER_APP(
        HelloCinder042App,
        RendererGl(RendererGl::Options().msaa(16)),
        [&](App::Settings *settings){
            settings->setWindowSize(800, 600);
            settings->setFrameRate(60.0f);
		}
)