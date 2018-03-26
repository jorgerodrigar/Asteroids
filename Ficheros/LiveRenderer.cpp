#include "LiveRenderercpp.h"
#include "GameManager.h"

void LiveRenderer::render(GameObject* o, Uint32 time){
	GameManager* gm = static_cast<GameManager*>(o);

	SDL_Rect destRect;
	destRect.w = Tam*0.7;
	destRect.h = Tam;
	destRect.x = -Tam;
	destRect.y = 0;

	//pintamos las vidas
	for (int i = 0; i < gm->getLives(); i++) {
		destRect.x += Tam;
		gm->getGame()->getResources()->getImageTexture(Resources::chewbacca)->render(o->getGame()->getRenderer(), destRect);
	}
};