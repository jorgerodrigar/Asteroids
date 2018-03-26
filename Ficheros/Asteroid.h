#ifndef ASTEROID_H_
#define ASTEROID_H_

#include "Container.h"

class Asteroid : public Container {
public:
	Asteroid(SDLGame* game) : Container(game){
		setWidth(40);
		setHeight(40);
		generations_ = 1;
	}
	virtual ~Asteroid(){}
	virtual void setGenerations(int generations) { generations_ = generations; }
	virtual int getGenerations() { return generations_; }
	bool getActive(){ return active; }
	void setActive(bool b){ active = b; }
	void reduceTam() { 
		setWidth(width_ / 2);
		setHeight(height_ / 2);
	}
private:
	int generations_;
	bool active = false;
};

#endif /* ASTEROID_H_ */