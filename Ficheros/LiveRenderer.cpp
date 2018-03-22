#include "LiveRenderercpp.h"
#include "GameManager.h"

void LiveRenderer::render(GameObject* o, Uint32 time){
	GameManager* gm = static_cast<GameManager*>(o);

	SDLGame* game = gm->getGame();

	Texture* vida = game->getResources()->getImageTexture(Resources::chewbacca);

	SDL_Rect destRect;
	destRect.w = Tam*0.7;
	destRect.h = Tam;
	destRect.x = -Tam;
	destRect.y = 0;

	//pintamos las vidas
	
	for (int i = 0; i < gm->getLives(); i++) {
		destRect.x += Tam;
		vida->render(o->getGame()->getRenderer(), destRect);
	}
};