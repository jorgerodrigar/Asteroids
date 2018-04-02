#include "BadgeTimer.h"
#include "GameManager.h"

void BadgeTimer::update(GameObject * o, Uint32 time)
{
	if (on_ && timeInterval_ + timeOn_ < time) {
		on_ = false;
		static_cast<GameManager*>(o)->setBadge(false);
	}
}
