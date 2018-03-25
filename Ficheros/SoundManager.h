#pragma once
#include "Observer.h"

class SoundManager : public Observer {
public:
	SoundManager(SDLGame* game) :game_(game) {}
	virtual ~SoundManager() {}
	virtual void receive(Message* msg);
private:
	SDLGame* game_;
};

