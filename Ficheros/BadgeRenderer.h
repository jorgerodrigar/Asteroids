#pragma once

#include "RenderComponent.h"

class BadgeRenderer : public RenderComponent {
private:
	int Tam = 50;
public:
	BadgeRenderer() {}
	virtual ~BadgeRenderer() {}
	virtual void render(GameObject* o, Uint32 time);
};


