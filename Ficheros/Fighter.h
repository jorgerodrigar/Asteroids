#ifndef FIGHTER_H_
#define FIGHTER_H_

#include "Container.h"

//clase que controlara el jugador, la nave
class Fighter : public Container {
public:
	Fighter(SDLGame* game, int id);
	virtual ~Fighter(){}
	int getId() { return id_; }//devuelve el id de la nave
	bool getActive() { return active; }
	void setActive(bool b) { active = b; }
	//InputComponent* getGunObservable() { return gun; }//devuelve el componente GunInputComponent
	//para poder establecerlo como observable de StarWarsBulletsManager en la escena, y asi poder enviarle el mensaje de disparo
private:
	int id_;//id de cada nave por si hay varias en escena
	bool active = false;
	/*SDL_Rect rect;
	//componentes de pintado, rotacion, disparo, toroide y aceleracion
	RenderComponent* naveSprite;
	InputComponent* rotation;
	InputComponent* gun;
	PhysicsComponent* circular;
	InputComponent* acceleration;*/
};

#endif /* FIGHTER_H_ */