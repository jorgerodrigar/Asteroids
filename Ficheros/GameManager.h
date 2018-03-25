#pragma once
#include "GameObject.h"
#include "Observable.h"
#include "Messages.h"
#include "GameCtrlInputComponent.h"
#include "GameMsgRenderer.h"
#include "ScoreRenderer.h"
#include "LiveRenderercpp.h"
class BadgeTimer;

class GameManager : public Container, public Observer, public Observable {
public:
	GameManager(SDLGame* game);
	virtual ~GameManager() {};
	bool isGameOver() const { return gameOver; }
	int getLives() const { return vidas; }
	bool isRunning() const { return running; }
	void setRunning(bool run) {
		if (running != run) {
			running = run;
			Message m = { running ? ROUND_START : ROUND_OVER };
			send(&m);
		}
	}
	void setGameOver(bool Gover) { if (gameOver != Gover) gameOver = Gover; }
	int getScore() const { return score; }
	void setScore(int i) { score = i; }
	void setBadge(bool b);
	void resetGame() { setScore(0); vidas = 3; gameOver = false; }//reinicia el juego (llamado desde InputCtrl cuando pulsamos una tecla y se ha acabado la partida)
	void receive(Message* msg);
private:
	bool gameOver = false, running = false;
	int vidas = 3, score = 0;
	RenderComponent* scoreRenderer_;
	RenderComponent* livesRenderer_;
	InputComponent* gameCtrl_;
	RenderComponent* gameMsg_;
	PhysicsComponent* badgeTimer_;
};