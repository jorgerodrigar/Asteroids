#ifndef EXAMPLEGAME_H_
#define EXAMPLEGAME_H_

#include <vector>

#include "SDLGame.h"
#include "StarWarsBulletsManager.h"
#include "CollisionManager.h"
#include "GameManager.h"

class ExampleGame: public SDLGame {

public:
	ExampleGame();
	virtual ~ExampleGame();

	// from SDLGame
	void start();
	void stop();

private:
	void initGame();
	void closeGame();
	void handleInput(Uint32 time);
	void update(Uint32 time);
	void render(Uint32 time);

	const static int _WINDOW_WIDTH_ = 640;
	const static int _WINDOW_HEIGHT_ = 480;
	bool exit_;
	std::vector<GameObject*> actors_;

	FightersManager* nave;
	StarWarsBulletsManager* bulletManager;
	AstroidsManager* asteroidManager;
	CollisionManager* colisionManager;
	GameManager* gameManager;
};

#endif /* EXAMPLEGAME_H_ */
