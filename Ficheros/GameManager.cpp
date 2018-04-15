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
		if (running)vidas--;//se restan vidas, se desactivan los powerup y se acaba la ronda
		setAllBadgesFalse();
		scoreRound = 0;
		actualBadge = 0;
		setRunning(false);
		if (vidas == 0)setGameOver(true);//si no tienes vidas se acaba la partida
		break;
	case BULLET_ASTROID_COLLISION://si una bala choca con un asteroide
		score++;//se suman los puntos
		scoreRound++;
		if (scoreRound % 10 == 0) {
			setBadge(true, (MessageId)(BEGINBADGES + actualBadge * 2));//se activan powerUps dependiendo de los puntos que llevemos
			if (actualBadge == NUMBADGES - 1) actualBadge = 0;//si el badge que tocaba era el ultimo, volvemos a empezar por el primero
			else actualBadge++;
		}
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
	setAllBadgesFalse();//desactiva primero todos para no tener varios a la vez
	send(&msg);//se activa el correspondiente y se inicia el contador de tiempo
	if (b) static_cast<BadgeTimer*>(&badgeTimer_)->start(10000);
}
