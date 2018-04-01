#include "GameManager.h"
#include "BadgeTimer.h"

//inicializamos los componentes que rigen el funcionamiento del juego (inicio/fin de rondas, hud, etc.)
GameManager::GameManager(SDLGame* game): Container(game) {
	gameCtrl_ = new GameCtrlInputComponent();
	gameMsg_ = new GameMsgRenderer();
	scoreRenderer_ = new ScoreRenderer();
	livesRenderer_ = new LiveRenderer();
	badgeTimer_ = new BadgeTimer();

	addInputComponent(gameCtrl_);
	addRenderComponent(gameMsg_);
	addRenderComponent(scoreRenderer_);
	addRenderComponent(livesRenderer_);
	addPhysicsComponent(badgeTimer_);
}

//recibidor de mensajes
void GameManager::receive(Message* msg) {
	switch (msg->id_) {
	case ASTROID_FIGHTER_COLLISION://si un asteroide choca con la nave
		if (running)vidas--;//se restan vidas, se desactiva el powerup y se acaba la ronda
		setBadge(false);
		setRunning(false);
		if (vidas == 0)setGameOver(true);//si no tienes vidas se acaba la partida
		break;
	case BULLET_ASTROID_COLLISION://si una bala choca con un asteroide
		score++;//se suman los puntos
		if (score % 10 == 0)setBadge(true);//cada diez puntos se activa el powerup
		break;
	case NO_MORE_ATROIDS://si no quedan asteroides
		setBadge(false);//se desactiva el powerup y se acaba la ronda y la partida
		setRunning(false);
		setGameOver(true);
		break;
		
	}
}

//activa o desactiva el powerup
void GameManager::setBadge(bool b) {
	if (b) {
		Message msg = { BADGE_ON };
		send(&msg);
		static_cast<BadgeTimer*>(badgeTimer_)->start(10000);
	}
	else {
		Message msg = { BADGE_OFF };
		send(&msg);
	}
}
