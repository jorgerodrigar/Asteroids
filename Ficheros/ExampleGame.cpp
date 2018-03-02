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

	//inicializamos la nave y el gestor de balas
	nave = new Fighter(this, 0);
	bulletManager = new StarWarsBulletsManager(this, nave);

	//lo añadimos a la lista de actores para ser pintados y actualizados
	actors_.push_back(nave);
	actors_.push_back(bulletManager);

	//establecemos el componente de disparo de la nave como observable del gestor de balas para poder enviarle el mensaje de disparo
	dynamic_cast<Observable*>(nave->getGunObservable())->registerObserver(bulletManager);
}

void ExampleGame::closeGame() {
	if (nave != nullptr)delete nave;
	if (bulletManager != nullptr)delete bulletManager;
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
	SDL_SetRenderDrawColor(getRenderer(), COLOR(0x00AAAAFF));
	SDL_RenderClear(getRenderer());

	for (GameObject* o : actors_) {
		o->render(time);
	}

	SDL_RenderPresent(getRenderer());
}

