#pragma once
#include "GameObject.h"
#include "Observable.h"
#include "Messages.h"
#include "GameCtrlInputComponent.h"
#include "GameMsgRenderer.h"
#include "ScoreRenderer.h"
#include "LiveRenderercpp.h"
#include "checkML.h"
#include "BadgeTimer.h"
#include <list>

//gestor del juego
class GameManager : public Container, public Observer, public Observable {
public:
	GameManager(SDLGame* game);
	virtual ~GameManager() {
	};
	bool isGameOver() const { return gameOver; }
	int getLives() const { return vidas; }
	bool isRunning() const { return running; }
	void setRunning(bool run) {
		if (running != run) {
			running = run;//dependiendo de si esta running o no se manda un mensaje de empezar/acabar ronda
			Message m = { running ? ROUND_START : ROUND_OVER };
			send(&m);
		}
	}
	void setGameOver(bool Gover) { if (gameOver != Gover) gameOver = Gover; }
	int getScore() const { return score; }
	void setScore(int i) { score = i; }
	void setBadge(bool b, Message msg);
	void resetGame() { setScore(0); vidas = 3; gameOver = false; }//reinicia el juego (llamado desde InputCtrl cuando pulsamos una tecla y se ha acabado la partida)
	void receive(Message* msg);
	//desactiva todos los badges
	void setAllBadgesFalse() {//recorre el enumerador de mensajes y manda todos los correspondientes a desactivar badges
		for (int i = BEGINBADGES + 1; i < BEGINBADGES + 1 + NUMBADGES*2; i+=2) {
			Message m = (MessageId)i;
			send(&m);
		}
	}
private:
	bool gameOver = false, running = false;
	int vidas = 3, score = 0, scoreRound = 0;
	ScoreRenderer scoreRenderer_;
	LiveRenderer livesRenderer_;
	GameCtrlInputComponent gameCtrl_;
	GameMsgRenderer gameMsg_;
	BadgeTimer badgeTimer_;
	const int BEGINBADGES = 9;//posicion en la que empiezan los mensajesde quitar badge
	const int NUMBADGES = 3;//numero de badges que se pueden conseguir
	int actualBadge = 0;//badge siguiente que cogeremos al destruir asteroides
};