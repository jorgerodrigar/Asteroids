#include "BadgeRenderer.h"
#include "GameManager.h"

void BadgeRenderer::render(GameObject* o, Uint32 time) {
	SDL_Rect destRect;
	destRect.w = textura->getWidth();
	destRect.h = textura->getHeight();
	destRect.x = o->getPosition().getX() + x_ - textura->getWidth()/2;
	destRect.y = o->getPosition().getY() + y_ - textura->getHeight()/2;

	//pintamos el simbolo de powerUp
	textura->render(o->getGame()->getRenderer(), destRect);
};
