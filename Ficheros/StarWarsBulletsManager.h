#pragma once
#include "BulletsManager.h"
#include "Bullet.h"
#include <algorithm>

using namespace std;

class StarWarsBulletsManager : public GameObject, public BulletsManager{
private:
	std::vector<Bullet*> bullets;
	RenderComponent* bulletRenderer_;
	PhysicsComponent* bulletPhysics_;
	Fighter* player;
	
	Bullet* getBullet();
	virtual void receive(Message* msg);
	virtual void shoot(Vector2D position, Vector2D velocity);
public:
	StarWarsBulletsManager(SDLGame* game, Fighter* nave): GameObject(game), player(nave) {
		bulletRenderer_ = new FillRectRenderer();
		bulletPhysics_ = new BasicMotionPhysics();
	}
	~StarWarsBulletsManager() {
		for (int i = 0; i < bullets.size();i++) delete(bullets[i]);
	}

	virtual void shoot(Vector2D p, Vector2D v);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	virtual void handleInput(Uint32 time, const SDL_Event& event) {}

	virtual std::vector<Bullet*>& getBullets() { return bullets; }
};

