#include "GameManager.h"
#include "BadgeTimer.h"

void GameManager::receive(Message* msg) {
	switch (msg->id_) {
	case ASTROID_FIGHTER_COLLISION:
		vidas--;
		setBadge(false);
		setRunning(false);
		if (vidas == 0)setGameOver(false);
		break;
	case BULLET_ASTROID_COLLISION:
		score++;
		if (score % 10 == 0)setBadge(true);
		break;
	case NO_MORE_ATROIDS:
		setBadge(false);
		setRunning(false);
		setGameOver(false);
		break;
		
	}
}

void GameManager::setBadge(bool b) {
	if (b) {
		Message msg = { BADGE_ON };
		send(&msg);
		badgeTimer_->start(10);
	}
	else {
		Message msg = { BADGE_OFF };
		send(&msg);
	}
}
