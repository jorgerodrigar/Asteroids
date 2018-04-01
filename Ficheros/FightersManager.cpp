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
	gunComp1_ = new GunInputComponent(SDLK_SPACE, 5);
	gunComp2_ = new GunInputComponent(SDLK_SPACE, 100);//powerUp
	badgeRenderer_ = new BadgeRenderer();//simbolo del powerUp
	switcher = ComponentSwitcher(game_, fighter_);
	switcher.addMode({ gunComp1_, nullptr, nullptr, nullptr });
	switcher.addMode({ gunComp2_, nullptr, nullptr, nullptr });

	//y los añadimos
	fighter_->addRenderComponent(renderComp_);
	fighter_->addInputComponent(rotationComp_);
	fighter_->addPhysicsComponent(circulrMotoionComp_);
	fighter_->addInputComponent(accelerationComp_);
	switcher.setMode(0);

	//registramos los observadores de los componentes de disparo
	gunComp1_->registerObserver(bulletsManager);
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
		fighter_->setDirection(Vector2D(0, -1));
		fighter_->setActive(true);
		fighter_->setPosition(Vector2D(game_->getWindowWidth() / 2 - fighter_->getWidth() / 2, game_->getWindowHeight() / 2 - fighter_->getHeight() / 2));
		break;
	case ROUND_OVER://al final de la ronda desactivamos al caza
		fighter_->setActive(false);
		break;
	case BADGE_ON:
		fighter_->delRenderComponent(badgeRenderer_);
		switcher.setMode(1);
		fighter_->addRenderComponent(badgeRenderer_);
		break;
	case BADGE_OFF:
		switcher.setMode(0);
		fighter_->delRenderComponent(badgeRenderer_);
		break;
	}
}
