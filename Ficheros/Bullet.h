#ifndef BULLET_H_
#define BULLET_H_

#include "FillRectRenderer.h"
#include "BasicMotionPhysics.h"

class Bullet : public Container {
public:
	Bullet(SDLGame* game);
	virtual ~Bullet(){}
	void setFighterId(int id);
	int getFighterId();
	void setActive(bool b) { active = b; }
	bool getActive() { return active; }
private:
	int fighterId_;
	bool active = false;
};

#endif /* BULLET_H_ */