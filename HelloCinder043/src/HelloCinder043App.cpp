#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "ParticleController.h"
#include "cinder/Perlin.h"

using namespace ci;
using namespace ci::app;
using namespace std;


class HelloCinder043App : public App {
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
    Perlin mPerlin;
};

void HelloCinder043App::setup() {
	mMousePressed = false;
    // create instance of Cinder's Perlin Noise class
    mPerlin = Perlin();
}

void HelloCinder043App::update() {
	getWindow()->setTitle("fps: " + to_string(getAverageFps()));
	if (mMousePressed) {
		mParticleController.addParticles(PARTICLES_TO_SPAWN, mMouseLocation, mMouseVelocity);
	}
    mParticleController.update(mPerlin, mMouseLocation);
}

void HelloCinder043App::draw() {
	gl::clear();
	mParticleController.draw();
}

void HelloCinder043App::mouseDown(MouseEvent event) {
	mMousePressed = true;
}

void HelloCinder043App::mouseUp(MouseEvent event) {
	mMousePressed = false;
}

void HelloCinder043App::mouseMove(MouseEvent event) {
	mMouseVelocity = (vec2(event.getPos()) - mMouseLocation);
	mMouseLocation = event.getPos();
}

void HelloCinder043App::mouseDrag(MouseEvent event) {
	mouseMove(event);
}


CINDER_APP(
        HelloCinder043App,
        RendererGl(RendererGl::Options().msaa(16)),
        [&](App::Settings *settings){
            settings->setWindowSize(800, 600);
            settings->setFrameRate(60.0f);
		}
)