#ifndef ASTEROID_H_
#define ASTEROID_H_

#include "Container.h"

class Asteroid : public Container {
public:
	Asteroid(SDLGame* game);
	virtual ~Asteroid();
	virtual void setGenerations(int generations);
	virtual int getGenerations();
private:
	int generations_;
};

#endif /* ASTEROID_H_ */