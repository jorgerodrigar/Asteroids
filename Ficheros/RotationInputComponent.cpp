#include "RotationInputComponent.h"


RotationInputComponent::RotationInputComponent(double angle, SDL_Keycode left, SDL_Keycode right) :angle_(angle), left_(left), right_(right){

}

void RotationInputComponent::handleInput(GameObject* o, Uint32 time, const SDL_Event& event){
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == left_) {
			Vector2D v = o->getDirection();
			v.rotate(angle_);
			o->setDirection(v);
		}
		else if (event.key.keysym.sym == right_) {
			Vector2D v = o->getDirection();
			v.rotate(-angle_);
			o->setDirection(v);
		}
	}
}
