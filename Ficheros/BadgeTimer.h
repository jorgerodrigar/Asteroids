#pragma once
#include "PhysicsComponent.h"
#include "GameManager.h"

class BadgeTimer : public PhysicsComponent {
public:
	BadgeTimer() {}
	virtual ~BadgeTimer() {}
	virtual void update(GameObject* o, Uint32 time) {
		if (on_ && timeInterval_ + timeOn_ < time) {
			on_ = false;
			static_cast<GameManager*>(o)->setBadge(false);
		}
	}
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
