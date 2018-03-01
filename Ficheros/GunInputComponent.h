#pragma once
#include "InputComponent.h"
#include "BulletsManager.h"
#include "Messages.h"

class GunInputComponent : public InputComponent, public Observable{
private:
	SDL_Keycode shoot_;
	BulletsManager* bulletsManager_;
public:
	GunInputComponent(BulletsManager* bulletsManager, SDL_Keycode shoot) : shoot_(shoot) { bulletsManager_ = bulletsManager; }
	~GunInputComponent(){}
	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& event);
};