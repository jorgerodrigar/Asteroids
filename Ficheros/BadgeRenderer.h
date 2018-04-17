#pragma once

#include "RenderComponent.h"
#include "checkML.h"

//pinta un sprite indicando que el jugador tiene el powerUp
class BadgeRenderer : public RenderComponent {
private:
	Texture* textura;
	int x_, y_;
public:
	BadgeRenderer() : x_(0), y_(0) {};
	BadgeRenderer(int x, int y, Texture* text) : x_(x), y_(y), textura(text) {}
	virtual ~BadgeRenderer() { textura = nullptr; }
	virtual void render(GameObject* o, Uint32 time);
	void changeImage(Texture* text) { textura = text; }
};


