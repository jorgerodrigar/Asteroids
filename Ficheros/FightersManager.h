#ifndef FIGHTERSMANAGER_H_
#define FIGHTERSMANAGER_H_
#include "GameObject.h"
#include "Observer.h"
#include "Fighter.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "RotationInputComponent.h"
#include "CircularMotionPhysics.h"
#include "AccelerationInputComponent.h"
#include "ImageRenderer.h"
#include "GunInputComponent.h"
#include "BadgeRenderer.h"
#include "ComponentSwitcher.h"
#include "checkML.h"

//gestor de naves
class FightersManager : public GameObject, public Observer {
public:
	FightersManager() {};
	FightersManager(SDLGame* game, Observer* bulletsManager);
	virtual ~FightersManager() {}
	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	Fighter* getFighter() { return fighter_; }
	virtual void receive(Message* msg);
private:
	Fighter* fighter_;
	CircularMotionPhysics* circulrMotoionComp_;
	AccelerationInputComponent* accelerationComp_;
	ImageRenderer* renderComp_;
	RotationInputComponent* rotationComp_;
	GunInputComponent* gunComp1_;
	GunInputComponent* gunComp2_; //powerUp
	BadgeRenderer* badgeRenderer_;//simbolo del powerup
	ComponentSwitcher switcher;
};
#endif /* FIGHTERSMANAGER_H_ */