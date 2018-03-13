#include "GunInputComponent.h"

//si se pulsa la tecla de disparo avisamos a StarWarsBulletsManager de que se ha disparado mediante un mensaje
void GunInputComponent::handleInput(GameObject* o, Uint32 time, const SDL_Event& event) {
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
		Message msg{ FIGHTER_SHOOT };
		send(&msg);
	}
}
