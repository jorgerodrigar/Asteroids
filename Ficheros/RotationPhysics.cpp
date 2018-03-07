#include "RotationPhysics.h"

void RotationPhysics::update(GameObject* o, Uint32 time){
			Vector2D v = o->getDirection();
			v.rotate(angle_);
			o->setDirection(v);
}