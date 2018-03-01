#include "CircularMotionPhysics.h"


CircularMotionPhysics::CircularMotionPhysics()
{
}


CircularMotionPhysics::~CircularMotionPhysics()
{
}

void CircularMotionPhysics::update(GameObject* o, Uint32 time){
	Vector2D position = o->getPosition();
	Vector2D velocity = o->getVelocity();

	position = position + velocity;
	double x = position.getX();
	double y = position.getY();

	toroide(o, x, y);

	position.setX(x);
	position.setY(y);

	o->setVelocity(velocity);
	o->setPosition(position);
}

void CircularMotionPhysics::toroide(GameObject* o, double& x, double& y) {
	if (y <= 0) {
		y = o->getGame()->getWindowHeight() - o->getHeight();
	}

	else if (y + o->getHeight() >= o->getGame()->getWindowHeight()) {
		y = 0;
	}

	if (x <= 0) {
		x = o->getGame()->getWindowWidth() - o->getWidth();
	}

	else if (x + o->getWidth() >= o->getGame()->getWindowWidth()) {
		x = 0;
	}
}
