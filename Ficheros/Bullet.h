#ifndef BULLET_H_
#define BULLET_H_

#include "FillRectRenderer.h"
#include "BasicMotionPhysics.h"
#include "Container.h"

//clase bala, lo que disparara el jugador
class Bullet : public Container {
public:
	///inicializamos los atributos
	Bullet(SDLGame* game) : Container(game) {
		setWidth(3);
		setHeight(5);
	}
	virtual ~Bullet(){}
	void setFighterId(int id) { fighterId_ = id; }//establece el id de la nave que la ha disparado
	int getFighterId() { return fighterId_; }//devuelve el id de la nave que la ha disparado
	void setActive(bool b) { active = b; }//establece una bala a activa o no
	bool getActive() { return active; }//devuelve si la bala esta activa o no
private:
	int fighterId_;//id de la nave que la ha instanciado (disparado)
	bool active = false;//booleano que indica si la bala esta activa, inicialmente no
};

#endif /* BULLET_H_ */