#pragma once
#include "Observer.h"
#include "SoundEffect.h"
#include "Music.h"

//gestor de sonidos y musica
class SoundManager : public Container, public Observer {
public:
	SoundManager(SDLGame* game) :Container(game) {}
	virtual ~SoundManager() {}
	virtual void receive(Message* msg);
};

