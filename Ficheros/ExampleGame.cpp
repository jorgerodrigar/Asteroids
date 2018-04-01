#include "ExampleGame.h"

ExampleGame::ExampleGame() :
		SDLGame("Example Game", _WINDOW_WIDTH_, _WINDOW_HEIGHT_) {
	initGame();
	exit_ = false;
}

ExampleGame::~ExampleGame() {
	closeGame();
}

void ExampleGame::initGame() {

	// hide cursor
	SDL_ShowCursor(0);

	//inicializamos el gestor de naves, el gestor de balas, el de asteroides y el de colisiones
	bulletManager = new StarWarsBulletsManager(this);
	asteroidManager = new AstroidsManager(this);
	nave = new FightersManager(this, bulletManager);
	bulletManager->setPlayer(nave->getFighter());
	colisionManager = new CollisionManager(this, bulletManager, asteroidManager, nave);
	gameManager = new GameManager(this);
	soundManager = new SoundManager(this);

	//los añadimos a la lista de actores para ser pintados y actualizados
	actors_.push_back(nave);
	actors_.push_back(bulletManager);
	actors_.push_back(asteroidManager);
	actors_.push_back(colisionManager);
	actors_.push_back(gameManager);
	actors_.push_back(soundManager);

	dynamic_cast<Observable*>(colisionManager)->registerObserver(bulletManager);
	dynamic_cast<Observable*>(colisionManager)->registerObserver(asteroidManager);
	dynamic_cast<Observable*>(colisionManager)->registerObserver(gameManager);
	dynamic_cast<Observable*>(asteroidManager)->registerObserver(gameManager);
	dynamic_cast<Observable*>(gameManager)->registerObserver(nave);
	dynamic_cast<Observable*>(gameManager)->registerObserver(bulletManager);
	dynamic_cast<Observable*>(gameManager)->registerObserver(asteroidManager);
	dynamic_cast<Observable*>(bulletManager)->registerObserver(soundManager);
	dynamic_cast<Observable*>(colisionManager)->registerObserver(soundManager);
	dynamic_cast<Observable*>(gameManager)->registerObserver(soundManager);
}

void ExampleGame::closeGame() {
	if (nave != nullptr)delete nave;
	if (bulletManager != nullptr)delete bulletManager;
	if (asteroidManager != nullptr)delete asteroidManager;
	if (colisionManager != nullptr)delete colisionManager;
	if (gameManager != nullptr)delete gameManager;
}

void ExampleGame::start() {
	exit_ = false;
	while (!exit_) {
		Uint32 startTime = SDL_GetTicks();

		handleInput(startTime);
		update(startTime);
		render(startTime);

		Uint32 frameTime = SDL_GetTicks() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}

void ExampleGame::stop() {
	exit_ = true;
}

void ExampleGame::handleInput(Uint32 time) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				exit_ = true;
				break;
				// Pressing f to toggle fullscreen.
			case SDLK_f:
				int flags = SDL_GetWindowFlags(window_);
				if (flags & SDL_WINDOW_FULLSCREEN) {
					SDL_SetWindowFullscreen(window_, 0);
				}
				else {
					SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN);
				}
				break;
			}
		}
		for (GameObject* o : actors_) {
			o->handleInput(time, event);
		}
	}
}

void ExampleGame::update(Uint32 time) {
	for (GameObject* o : actors_) {
		o->update(time);
	}
}

void ExampleGame::render(Uint32 time) {
	SDL_RenderClear(getRenderer());
	resources_->getImageTexture(Resources::deathStar)->render(renderer_,
	{ -100, 0, resources_->getImageTexture(Resources::deathStar)->getWidth(),resources_->getImageTexture(Resources::deathStar)->getHeight() });

	for (GameObject* o : actors_) {
		o->render(time);
	}

	SDL_RenderPresent(getRenderer());
}

