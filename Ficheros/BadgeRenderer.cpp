#include "BadgeRenderer.h"
#include "GameManager.h"

void BadgeRenderer::render(GameObject* o, Uint32 time) {
	SDL_Rect destRect;
	destRect.w = Tam;
	destRect.h = Tam;
	destRect.x = o->getPosition().getX();
	destRect.y = o->getPosition().getY();

	//pintamos el simbolo de powerUp
	o->getGame()->getResources()->getImageTexture(Resources::powerUp)->render(o->getGame()->getRenderer(), destRect);
};
