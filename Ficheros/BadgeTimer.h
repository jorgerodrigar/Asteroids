#pragma once
#include "PhysicsComponent.h"
#include "checkML.h"

//contador que quita el powerUp despues de un tiempo
class BadgeTimer : public PhysicsComponent {
public:
	BadgeTimer() {}
	virtual ~BadgeTimer() {}
	virtual void update(GameObject* o, Uint32 time);
	void start(Uint32 timeInterval) {
   		on_ = true;
		timeOn_ = SDL_GetTicks();
		timeInterval_ = timeInterval;
	}

private:
	bool on_ = false;
	Uint32 timeOn_;
	Uint32 timeInterval_;
};
