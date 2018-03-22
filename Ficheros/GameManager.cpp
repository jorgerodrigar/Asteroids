#include "GameManager.h"
#include "BadgeTimer.h"

//recibidor de mensajes
void GameManager::receive(Message* msg) {
	switch (msg->id_) {
	case ASTROID_FIGHTER_COLLISION://si un asteroide choca con la nave
		if (running)vidas--;//se restan vidas, se desactiva el powerup y se acaba la ronda
		setBadge(false);
		setRunning(false);
		if (vidas == 0)setGameOver(false);//si no tienes vidas se acaba la partida
		break;
	case BULLET_ASTROID_COLLISION://si una bala choca con un asteroide
		score++;//se suman los puntos
		if (score % 10 == 0)setBadge(true);//cada diez puntos se activa el powerup
		break;
	case NO_MORE_ATROIDS://si no quedan asteroides
		setBadge(false);//se desactiva el powerup y se acaba la ronda y la partida
		setRunning(false);
		setGameOver(false);
		break;
		
	}
}

//activa o desactiva el powerup
void GameManager::setBadge(bool b) {
	if (b) {
		Message msg = { BADGE_ON };
		send(&msg);
		//static_cast<BadgeTimer*>(badgeTimer_)->start(10);
	}
	else {
		Message msg = { BADGE_OFF };
		send(&msg);
	}
}
