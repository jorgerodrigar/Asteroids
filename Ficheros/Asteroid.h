#ifndef ASTEROID_H_
#define ASTEROID_H_

#include "Container.h"

class Asteroid : public Container {
public:
	Asteroid(SDLGame* game) : Container(game){
		setWidth(70);
		setHeight(70);
	}
	virtual ~Asteroid(){}
	virtual void setGenerations(int generations) { generations_ = generations; }
	virtual int getGenerations() { return generations_; }
	bool getActive(){ return active; }
	void setActive(bool b){ active = b; }
private:
	int generations_;
	bool active = false;
};

#endif /* ASTEROID_H_ */