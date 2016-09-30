#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "ParticleController.h"

using namespace ci;
using namespace ci::app;
using namespace std;


class HelloCinder02App : public App {
public:
    void setup() override;
    void update() override;
    void draw() override;
private:
    ParticleController mParticleController;
};

void HelloCinder02App::setup() {
	mParticleController.addParticles(50);
}

void HelloCinder02App::update() {
    getWindow()->setTitle("fps: " + to_string(getAverageFps()));
	mParticleController.update();
}

void HelloCinder02App::draw() {
    gl::clear();
	mParticleController.draw();
}


CINDER_APP(
        HelloCinder02App,
        RendererGl(RendererGl::Options().msaa(16)),
        [&](App::Settings *settings){
            settings->setWindowSize(800, 600);
            settings->setFrameRate(60.0f);
		}
)