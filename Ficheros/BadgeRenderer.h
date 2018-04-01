#pragma once

#include "RenderComponent.h"

//pinta un sprite indicando que el jugador tiene el powerUp
class BadgeRenderer : public RenderComponent {
private:
	int Tam = 53;
public:
	BadgeRenderer() {}
	virtual ~BadgeRenderer() {}
	virtual void render(GameObject* o, Uint32 time);
};


