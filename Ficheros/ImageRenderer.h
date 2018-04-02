#ifndef IMAGERENDERER_H_
#define IMAGERENDERER_H_

#include "RenderComponent.h"

#include "checkML.h"
/*
 *
 */
class ImageRenderer: public RenderComponent {
public:
	ImageRenderer():image_(nullptr) {};
	ImageRenderer(Texture* image, SDL_Rect clip);
	virtual ~ImageRenderer();
	virtual void render(GameObject* o, Uint32 time);
private:
	Texture* image_;
	SDL_Rect clip_;
	double angle(GameObject* go);
};

#endif /* IMAGERENDERER_H_ */
