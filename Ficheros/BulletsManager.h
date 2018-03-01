#pragma once
#include "GameObject.h"
#include "Observable.h"
#include "Observer.h"

class BulletsManager:public Observable, public Observer {
public:
	BulletsManager() {}
	virtual ~BulletsManager() {}

	virtual std::vector<Bullet*>& getBullets() = 0;
};

