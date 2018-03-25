#include "BadgeRenderer.h"
#include "GameManager.h"

void BadgeRenderer::render(GameObject* o, Uint32 time) {
	Texture* powerUp = o->getGame()->getResources()->getImageTexture(Resources::chewbacca);

	SDL_Rect destRect;
	destRect.w = Tam*0.7;
	destRect.h = Tam;
	destRect.x = o->getGame()->getWindowWidth() - Tam;
	destRect.y = 0;

	//pintamos el simbolo de powerUp
	powerUp->render(o->getGame()->getRenderer(), destRect);
};
