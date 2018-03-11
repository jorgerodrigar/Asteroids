#include "FightersManager.h"

FightersManager::FightersManager(SDLGame * game, Observer * bulletsManager) : GameObject(game)
{
	fighter_ = new Fighter(game, 0);
	
	//-------------------PROVISONAL, TODO ESTO IRA POR MENSAJES(MAS ABAJO)----------------
	fighter_->setActive(true);
	fighter_->setPosition(Vector2D(game->getWindowWidth() / 2 - getWidth(), game->getWindowHeight() / 2 - getHeight()));
	//------------------------------------------------------------------------------------

	renderComp_ = new ImageRenderer(game->getResources()->getImageTexture(Resources::halcon), SDL_Rect{ 0, 0, game->getResources()->getImageTexture(Resources::halcon)->getWidth(),
	game->getResources()->getImageTexture(Resources::halcon)->getHeight() }); //inicializamos los componentes
	rotationComp_ = new RotationInputComponent(5, SDLK_LEFT, SDLK_RIGHT);
	circulrMotoionComp_ = new CircularMotionPhysics();
	accelerationComp_ = new AccelerationInputComponent(SDLK_UP, SDLK_DOWN, 1, 3, 0.8);
	gunComp1_ = new GunInputComponent(SDLK_SPACE);
	gunComp2_ = new GunInputComponent(SDLK_SPACE);
	fighter_->addRenderComponent(renderComp_); //y los añadimos
	fighter_->addInputComponent(rotationComp_);
	fighter_->addPhysicsComponent(circulrMotoionComp_);
	fighter_->addInputComponent(accelerationComp_);
	fighter_->addInputComponent(gunComp1_);

	gunComp1_->registerObserver(bulletsManager);//registramos los observadores de los componentes de disparo
	gunComp2_->registerObserver(bulletsManager);
}

void FightersManager::handleInput(Uint32 time, const SDL_Event & event)
{
	if (fighter_->getActive()) {
		fighter_->handleInput(time, event);//si esta activo llamamos al metodo del padre
	}
}

void FightersManager::update(Uint32 time)
{
	if (fighter_->getActive()) {
		fighter_->update(time);//si esta activo llamamos al metodo del padre
	}
}

void FightersManager::render(Uint32 time)
{
	if (fighter_->getActive()) {
		fighter_->render(time);//si esta activo llamamos al metodo del padre
	}
}

void FightersManager::receive(Message* msg) {
	switch (msg->id_) {
	case ROUND_START:
		fighter_->setActive(true);
		fighter_->setPosition(Vector2D(game_->getWindowWidth() / 2 - getWidth(), game_->getWindowHeight() / 2 - getHeight()));
			break;
	case ROUND_OVER:
		fighter_->setActive(false);
			break;
	case BADGE_ON:
		/*fighter_->delInputComponent(gunComp1_); //provisonal, aun no estan implementadas las mejoras(badges)
		fighter_->addInputComponent(gunComp2_);
		fighter_->addRenderComponent(badgeRenderer_);*/
			break;
	case BADGE_OFF:
		/*fighter_->delInputComponent(gunComp2_); //provisonal, aun no estan implementadas las mejoras(badges)
		fighter_->addInputComponent(gunComp1_);
		fighter_->delRenderComponent(badgeRenderer_);*/
			break;
	}
}
