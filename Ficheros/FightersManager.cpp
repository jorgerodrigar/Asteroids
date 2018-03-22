#include "FightersManager.h"

FightersManager::FightersManager(SDLGame * game, Observer * bulletsManager) : GameObject(game)
{
	fighter_ = new Fighter(game, 0);

	//inicializamos los componentes
	renderComp_ = new ImageRenderer(game->getResources()->getImageTexture(Resources::halcon), SDL_Rect{ 0, 0, game->getResources()->getImageTexture(Resources::halcon)->getWidth(),
	game->getResources()->getImageTexture(Resources::halcon)->getHeight() });
	rotationComp_ = new RotationInputComponent(5, SDLK_LEFT, SDLK_RIGHT);
	circulrMotoionComp_ = new CircularMotionPhysics();
	accelerationComp_ = new AccelerationInputComponent(SDLK_UP, SDLK_DOWN, 1, 3, 0.8);
	gunComp1_ = new GunInputComponent(SDLK_SPACE);
	gunComp2_ = new GunInputComponent(SDLK_SPACE);//powerUp

	//y los a�adimos
	fighter_->addRenderComponent(renderComp_);
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

//recibidor de mensajes
void FightersManager::receive(Message* msg) {
	switch (msg->id_) {
	case ROUND_START://al comienzo de la ronda  ponemos velocidad del caza a 0 y la posicion inicial
		fighter_->setVelocity(Vector2D(0, 0));
		fighter_->setActive(true);
		fighter_->setPosition(Vector2D(game_->getWindowWidth() / 2 - fighter_->getWidth()/2, game_->getWindowHeight() / 2 - fighter_->getHeight()/2));
			break;
	case ROUND_OVER://al final de la ronda desactivamos al caza
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
