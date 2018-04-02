#pragma once
#include "PhysicsComponent.h"
#include "checkML.h"

class CircularMotionPhysics :
	public PhysicsComponent
{
public:
	CircularMotionPhysics();
	~CircularMotionPhysics();
	virtual void update(GameObject* o, Uint32 time);
	void toroide(GameObject* o, double& x, double& y);
};

