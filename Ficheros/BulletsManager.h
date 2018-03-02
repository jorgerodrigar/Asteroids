#pragma once
#include "GameObject.h"
#include "Observable.h"
#include "Observer.h"

//clase gestora de las balas, puede mandar y recibir mensajes (abstracta pura)
class BulletsManager:public Observable, public Observer {
public:
	BulletsManager() {}
	virtual ~BulletsManager() {}

	virtual std::vector<Bullet*>& getBullets() = 0;
};

