#include "AccelerationInputComponent.h"


AccelerationInputComponent::AccelerationInputComponent(SDL_Keycode acelerar, SDL_Keycode desacelerar, double thrust, double velLimit, double reduction)
	:acc_(acelerar), desacc_(desacelerar), thrust(thrust), velLimit(velLimit), reductionFact(reduction) {

}

AccelerationInputComponent::~AccelerationInputComponent()
{
}

void AccelerationInputComponent::handleInput(GameObject* o, Uint32 time, const SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == acc_) {
			Vector2D dir = o->getDirection();
			dir.setX(-dir.getX());
			Vector2D vel = o->getVelocity();
			vel = vel + dir*thrust;
			if (vel.magnitude() > velLimit) {
				vel.normalize();
				vel = vel*velLimit;
			}
			o->setVelocity(vel);
		}
		else if (event.key.keysym.sym == desacc_) {
			Vector2D vel = o->getVelocity();
			vel = vel*reductionFact;
			if (vel.magnitude() < 0.1)vel.set(0, 0);
			o->setVelocity(vel);
		}
	}
}
