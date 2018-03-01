#pragma once
#include "InputComponent.h"

class AccelerationInputComponent : public InputComponent {
private:
	SDL_Keycode acc_;
	SDL_Keycode desacc_;
	double thrust;
	double velLimit;
	double reductionFact;

public:
	AccelerationInputComponent(SDL_Keycode acelerar, SDL_Keycode desacelerar, double thrust, double velLimit, double reduction);
	~AccelerationInputComponent();
	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& event);
};

