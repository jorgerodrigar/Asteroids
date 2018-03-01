#ifndef FIGHTER_H_
#define FIGHTER_H_

#include "Container.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "RotationInputComponent.h"
#include "CircularMotionPhysics.h"
#include "AccelerationInputComponent.h"
#include "ImageRenderer.h"
#include "GunInputComponent.h"
#include "BulletsManager.h"

class Fighter : public Container {
public:
	Fighter(SDLGame* game, int id, BulletsManager* bulletsManager);
	virtual ~Fighter(){}
	int getId();
private:
	int id_;
	SDL_Rect rect;
	BulletsManager* bulletsManager;
	RenderComponent* naveSprite;
	InputComponent* rotation;
	InputComponent* gun;
	PhysicsComponent* circular;
	InputComponent* acceleration;
};

#endif /* FIGHTER_H_ */