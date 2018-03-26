#pragma once
#include "InputComponent.h"
#include "Messages.h"
#include "Observable.h"

//componente que se encarga de mandar un mensaje a StarWarsBulletsManager cuando pulsamos la tecla de disparo
class GunInputComponent : public InputComponent, public Observable{
private:
	SDL_Keycode shoot_;//tecla de disparo
	const int timeRefresh = 3000;
	int maxShots;
	int timeSinceLastShot = 0, timeSinceLastUpdate = 0;
	bool tiempoIniciado = false;
	double velocity = 0;
public:
	GunInputComponent(SDL_Keycode shoot, int maxShots) : shoot_(shoot), maxShots(maxShots) {}
	~GunInputComponent(){}
	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& event);
};