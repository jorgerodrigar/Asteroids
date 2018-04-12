#include "GameManager.h"


//inicializamos los componentes que rigen el funcionamiento del juego (inicio/fin de rondas, hud, etc.)
GameManager::GameManager(SDLGame* game): Container(game) {
	gameCtrl_ = GameCtrlInputComponent();
	gameMsg_ =  GameMsgRenderer();
	scoreRenderer_ = ScoreRenderer();
	livesRenderer_ = LiveRenderer();
	badgeTimer_ = BadgeTimer();

	addInputComponent(&gameCtrl_);
	addRenderComponent(&gameMsg_);
	addRenderComponent(&scoreRenderer_);
	addRenderComponent(&livesRenderer_);
	addPhysicsComponent(&badgeTimer_);
}

//recibidor de mensajes
void GameManager::receive(Message* msg) {
	switch (msg->id_) {
	case ASTROID_FIGHTER_COLLISION://si un asteroide choca con la nave
		if (running)vidas--;//se restan vidas, se desactiva el powerup y se acaba la ronda
		setAllBadgesFalse();
		scoreRound = 0; cout << scoreRound;
		setRunning(false);
		if (vidas == 0)setGameOver(true);//si no tienes vidas se acaba la partida
		break;
	case BULLET_ASTROID_COLLISION://si una bala choca con un asteroide
		score++;//se suman los puntos
		if(!badge) scoreRound++;
		if (scoreRound % 30 == 0)setBadge(true, MULTI_ON);//se activan powerUps dependiendo de los puntos que llevemos
		else if (scoreRound % 20 == 0)setBadge(true, SUPER_ON);
		else if (scoreRound % 10 == 0)setBadge(true, BADGE_ON);
		break;
	case NO_MORE_ATROIDS://si no quedan asteroides
		setAllBadgesFalse();
		setRunning(false);
		setGameOver(true);
		break;
		
	}
}

//activa o desactiva el powerup
void GameManager::setBadge(bool b, Message msg) {
	send(&msg);
	badge = b;
	if (b) static_cast<BadgeTimer*>(&badgeTimer_)->start(10000);
}
