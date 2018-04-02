#pragma once
#include "InputComponent.h"
#include "checkML.h"

class RotationInputComponent : public InputComponent {
private:
	double angle_;
	SDL_Keycode left_;
	SDL_Keycode right_;

public:
	RotationInputComponent(double angle, SDL_Keycode left, SDL_Keycode right);
	~RotationInputComponent(){}
	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& event);
};

