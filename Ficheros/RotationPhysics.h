#pragma once
#include "PhysicsComponent.h"
#include "checkML.h"

class RotationPhysics : public PhysicsComponent {
private:
	double angle_;

public:
	RotationPhysics(double angle) :angle_(angle){};
	~RotationPhysics(){}
	virtual void update(GameObject* o, Uint32 time);
};