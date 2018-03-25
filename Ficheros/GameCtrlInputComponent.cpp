#include "GameCtrlInputComponent.h"
#include "GameManager.h"

GameCtrlInputComponent::GameCtrlInputComponent() {
}

GameCtrlInputComponent::~GameCtrlInputComponent() {
}

void GameCtrlInputComponent::handleInput(GameObject* o, Uint32 time, const SDL_Event& event) {

	GameManager* gm = static_cast<GameManager*>(o);

	if (event.type == SDL_KEYDOWN) {

		// si pulsamos cualquier tecla y no estabamos jugando (ronda acabada) empieza una nueva ronda
		if (!gm->isRunning()) {
			gm->setRunning(true);

			// si ademas se habia acabdo el juego lo reiniciamos (puntos y vidas)
			if (gm->isGameOver()) {
				gm->resetGame();
			}
		}
	}

}
