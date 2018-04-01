#include "ExampleGame.h"

ExampleGame::ExampleGame() ://inicializamos el gestor de naves, el gestor de balas, el de asteroides, el de colisiones, el de juego y el de sonido
	SDLGame("Example Game", _WINDOW_WIDTH_, _WINDOW_HEIGHT_), bulletManager(StarWarsBulletsManager(this)), asteroidManager(AstroidsManager(this)), nave(FightersManager(this, &bulletManager)),
	colisionManager(CollisionManager(this, &bulletManager, &asteroidManager, &nave)), gameManager(GameManager(this)), soundManager(SoundManager(this))
{
	initGame();
	exit_ = false;

	//añadimos la nave del jugador al gestor de naves
	bulletManager.setPlayer(nave.getFighter());
}

ExampleGame::~ExampleGame() {
	closeGame();
}

void ExampleGame::initGame() {

	// hide cursor
	SDL_ShowCursor(0);

	//establecemos observers y observables
	dynamic_cast<Observable*>(&colisionManager)->registerObserver(&bulletManager);
	dynamic_cast<Observable*>(&colisionManager)->registerObserver(&asteroidManager);
	dynamic_cast<Observable*>(&colisionManager)->registerObserver(&gameManager);
	dynamic_cast<Observable*>(&asteroidManager)->registerObserver(&gameManager);
	dynamic_cast<Observable*>(&gameManager)->registerObserver(&nave);
	dynamic_cast<Observable*>(&gameManager)->registerObserver(&bulletManager);
	dynamic_cast<Observable*>(&gameManager)->registerObserver(&asteroidManager);
	dynamic_cast<Observable*>(&bulletManager)->registerObserver(&soundManager);
	dynamic_cast<Observable*>(&colisionManager)->registerObserver(&soundManager);
	dynamic_cast<Observable*>(&gameManager)->registerObserver(&soundManager);

	//los añadimos a la lista de actores para ser pintados y actualizados
	//el soundManager no hace falta porque solo recibe mensajes
	actors_.push_back(&bulletManager);
	actors_.push_back(&nave);
	actors_.push_back(&asteroidManager);
	actors_.push_back(&colisionManager);
	actors_.push_back(&gameManager);
}

void ExampleGame::closeGame()
{
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
	SDL_RenderClear(getRenderer());//pintamos el fondo
	resources_->getImageTexture(Resources::deathStar)->render(renderer_,
	{ -100, 0, resources_->getImageTexture(Resources::deathStar)->getWidth(),resources_->getImageTexture(Resources::deathStar)->getHeight() });

	//y lo demas
	for (GameObject* o : actors_) {
		o->render(time);
	}

	SDL_RenderPresent(getRenderer());
}

