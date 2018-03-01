#include "ImageRenderer.h"

ImageRenderer::ImageRenderer(Texture* image, SDL_Rect clip) : image_(image), clip_(clip) {
}

ImageRenderer::~ImageRenderer() {
}

void ImageRenderer::render(GameObject* o, Uint32 time) {
	SDL_Rect rect
			RECT(o->getPosition().getX(), o->getPosition().getY(),
					o->getWidth(), o->getHeight());

	image_->render(o->getGame()->getRenderer(), rect, angle(o), &clip_);
}

double ImageRenderer::angle(GameObject* go){
	Vector2D d = go->getDirection();
	Vector2D origen(0, -1);

	return d.angle(origen);
}
