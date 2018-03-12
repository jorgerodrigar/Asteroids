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
private:
	int id_;//id de cada nave por si hay varias en escena
	bool active = false;
};

#endif /* FIGHTER_H_ */