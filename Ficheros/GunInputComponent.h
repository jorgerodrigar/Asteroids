#pragma once
#include "InputComponent.h"
#include "Messages.h"
#include "Observable.h"

//componente que se encarga de mandar un mensaje a StarWarsBulletsManager cuando pulsamos la tecla de disparo
class GunInputComponent : public InputComponent, public Observable{
private:
	SDL_Keycode shoot_;//tecla de disparo
public:
	GunInputComponent(SDL_Keycode shoot) : shoot_(shoot) {}
	~GunInputComponent(){}
	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& event);
};