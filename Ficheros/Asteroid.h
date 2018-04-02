#ifndef ASTEROID_H_
#define ASTEROID_H_

#include "Container.h"
#include "checkML.h"

//asteroides que flotan por la pantalla
class Asteroid : public Container {
public:
	Asteroid(SDLGame* game) : Container(game){
		setWidth(40);//tamaño inicial y numero de veces que se divide al ser destruido
		setHeight(40);
		generations_ = 1;
	}
	virtual ~Asteroid(){}
	virtual void setGenerations(int generations) { generations_ = generations; }
	virtual int getGenerations() { return generations_; }
	bool getActive(){ return active; }//comprueban/establecen el asteroide a activo o no activo (pool de asteroides)
	void setActive(bool b){ active = b; }
	void reduceTam() { //reduce el tamaño del asteroide a la mitad (llamado cuando uno es destruido)
		setWidth(width_ / 2);
		setHeight(height_ / 2);
	}
private:
	int generations_;
	bool active = false;
};

#endif /* ASTEROID_H_ */