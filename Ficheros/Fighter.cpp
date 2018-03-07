#include "Fighter.h"

//inicializamos atributos y añadimos componentes
Fighter::Fighter(SDLGame* game, int id) : Container(game), id_(id){
	setWidth(53);
	setHeight(71);
	setPosition(Vector2D(game->getWindowWidth() / 2 - getWidth(), game->getWindowHeight() / 2 - getHeight()));
	Vector2D dir(0, -1);
	setDirection(dir);
	rect = { 0,0,53,71 };

	naveSprite = new ImageRenderer(game->getResources()->getImageTexture(Resources::halcon), rect);
	rotation = new RotationInputComponent(5, SDLK_LEFT, SDLK_RIGHT);
	circular = new CircularMotionPhysics();
	acceleration = new AccelerationInputComponent(SDLK_UP, SDLK_DOWN, 1, 3, 0.8);
	gun = new GunInputComponent(SDLK_SPACE);
	addRenderComponent(naveSprite);
	addInputComponent(rotation);
	addPhysicsComponent(circular);
	addInputComponent(acceleration);
	addInputComponent(gun);
}