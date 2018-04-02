#pragma once
#include "GameObject.h"
#include "Observable.h"
#include "BulletsManager.h"
#include "AsteroidsManager.h"
#include "FightersManager.h"
#include "Collisions.h"
#include "Messages.h"
#include "checkML.h"

//gestor de colisiones
class CollisionManager : public GameObject, public Observable {
public:
	CollisionManager(SDLGame* game, BulletsManager* bulletsManager,
		AstroidsManager* astroidManager, FightersManager* ﬁghtersManager) :
		GameObject(game), bulletsManager_(bulletsManager), 
		astroidsManager_(astroidManager), ﬁghtersManager_(ﬁghtersManager) {}

	virtual ~CollisionManager() {}
	virtual void handleInput(Uint32 time, const SDL_Event& event) {}
	virtual void update(Uint32 time);
	virtual void render(Uint32 time) {}
private:
	BulletsManager* bulletsManager_;
	AstroidsManager* astroidsManager_;
	FightersManager* ﬁghtersManager_;
};
