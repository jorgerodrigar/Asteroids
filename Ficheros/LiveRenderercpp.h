#ifndef LIVERENDERERCPP_H_
#define LIVERENDERERCPP_H_

#include "RenderComponent.h"
#include "checkML.h"

class LiveRenderer : public RenderComponent {
private:
	int Tam = 50;
public:
	LiveRenderer(){}
	virtual ~LiveRenderer(){}
	virtual void render(GameObject* o, Uint32 time);
};

#endif /* LIVERENDERERCPP_H_ */